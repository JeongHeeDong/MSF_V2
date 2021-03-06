import ConfigParser
import sys
import os
import signal
import pandas as pd
import MySQLdb
import sqlalchemy

from sqlalchemy import create_engine


import Mobigen.Common.Log as Log

Log.Init()

G_SHUTDOWN = True


def Shutdown(sigNum=0, frame=0):
    global G_SHUTDOWN
    __LOG__.Trace("Recv Signal (%s)" % sigNum)
    G_SHUTDOWN = False


signal.signal(signal.SIGTERM, Shutdown)  # Sig Terminate : 15
signal.signal(signal.SIGINT, Shutdown)   # Sig Inturrupt : 2
signal.signal(signal.SIGHUP, Shutdown)  # Sig HangUp : 1
signal.signal(signal.SIGPIPE, Shutdown) # Sig Broken Pipe : 13


class Aggregator:
    """
        After reading file(ex: .csv) with path received on STDIN,
        aggregate the data and insert it

        Parameters
        ----------
        module : <string>
            module name
        section : <string>
            section name on config file
        conf_path : <string>
            config file path

        Note
        ----
        If you want to add other aggregation functions on self.agg_options
        refer to pandas official document.
        If you want to add new engine on self.engine_type
        refer to http://docs.sqlalchemy.org/en/latest/core/engines.html
    """
    def __init__(self, module, section, conf_path):
        self.module = module
        self.section = section
        self.conf_path = conf_path
        self.conf_parser = None
        self.agg_options = ["SUM", "MAX", "MIN", "MEAN", "COUNT"]
        self.cols_groupby = []
        self.agg = {}
        self.engine_type = {"Oracle": "oracle+cx_oracle://%s:%s@%s:%s/?service_name=%s",
                "MySQL": "mysql://%s:%s@%s:%s/%s"}

        self.get_conf_parser()
        self.set_config()
        self.set_logger()

    def get_conf_parser(self):
        self.conf_parser = ConfigParser.ConfigParser()
        if os.path.exists(self.conf_path):
            self.conf_parser.read(self.conf_path)
        else:
            print "Wrong config path"
            print "%s <SECTION> <CONFIG PATH>" % self.module
            sys.exit()

    def make_aggdict(self, cols, option):
        """
            Make dict parameter to be argument for pandas.DataFrame.agg function
            the argument has to be following form.
                {"<column>": [<agg func going to be applied1>, ...], ...}
                ex: {"duration": [min, max, mean]}

            Parameters
            ----------
            cols : <string>
                column going to be aggregated
            option : <string>
                aggregation function like SUM, COUNT, ..
        """
        if self.conf_parser.has_option(self.section, option):
            self.summation = self.conf_parser.get(self.section, option)
            for x in self.summation.split(','):
                col = x.strip()
                if col in self.agg.keys():
                    self.agg[col].append(option.lower())
                else:
                    self.agg[col] = [option.lower()]

    def set_config(self):
        if not self.conf_parser.has_option(self.section, "GROUPBY"):
            print "GROUPBY is not described in configuration file"
            sys.exit()
        self.cols_groupby = self.conf_parser.get(self.section, 'GROUPBY').split(',')

        if self.conf_parser.has_option(self.section, "SEP"):
            self.sep = self.conf_parser.get(self.section, 'SEP')

        for option in self.agg_options:
            self.make_aggdict(self.section, option)

        try:
            self.storage_type = self.conf_parser.get(self.section, 'STORAGE_TYPE')
            self.storage_confpath = self.conf_parser.get(self.section,
                                                         'STORAGE_CONFPATH')
            self.storage_section = self.conf_parser.get(self.section, 'STORAGE_SECTION')
            if self.conf_parser.has_option(self.section, 'STORAGE_TABLE'):
                self.storage_table = self.conf_parser.get(self.section, 'STORAGE_TABLE')
            self.parser_storage = ConfigParser.ConfigParser()
            if os.path.exists(self.storage_confpath):
                self.parser_storage.read(self.storage_confpath)
            else:
                print " STORAGE_CONFPATH error occured on config file"
                sys.exit()
        except:
            print "STORAGE configuration error occured on config file"
            sys.exit()


    def set_logger(self):
        self.logFilePath = 'Log'
        self.logFileSize = 1000000
        self.logFileCount = 10

        if (self.conf_parser != None):
            if self.conf_parser.get('Log', 'LogFilePath') != '':
                self.logFilePath = self.conf_parser.get('Log', 'LogFilePath')

            self.logFileSize = self.conf_parser.get('Log', 'LogFileSize')
            self.logFileCount = self.conf_parser.get('Log', 'LogFileCount')

            if not os.path.exists(self.logFilePath):
                print self.logFilePath
                os.makedirs(self.logFilePath)

            LOG_NAME = '%s/%s_%s.log' % (self.logFilePath,
                                         os.path.basename(self.module)[:-3],
                                         self.section)
            Log.Init(Log.CRotatingLog(os.path.expanduser(LOG_NAME),
                                      int(self.logFileSize),
                                      int(self.logFileCount)))

    def load_db(self, df, engine_str):
        conn_info = self.engine_type[self.storage_type] % engine_str
        try:
            engine = create_engine(conn_info, encoding='utf-8')
            conn = engine.connect()
            df.to_sql(name=self.storage_table, con=engine,
                      if_exists='append', index=False)
            __LOG__.Trace("query success to insert to %s" % self.storage_type)
        except sqlalchemy.exc.OperationalError:
            print exc.args

    def load_file(self, df):
        '''
            Add options on config file as you need.
            refer to http://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.to_csv.html#pandas.DataFrame.to_csv
        '''
        directory = self.parser_storage.get(self.storage_section, 'DIRPATH')
        filename = self.parser_storage.get(self.storage_section, 'FILENAME')
        path_ = os.path.join(directory, filename)

        item_keys = self.parser_storage.options(self.storage_section)
        item_keys.remove('dirpath')
        item_keys.remove('filename')
        parameters = {}
        for item_key in item_keys:
            if self.parser_storage.get(self.storage_section, item_key) == "True":
                parameters[item_key] = True
            elif self.parser_storage.get(self.storage_section, item_key) == "False":
                parameters[item_key] = False
            else:
                parameters[item_key] = self.parser_storage.get(self.storage_section,
                                                               item_key)
        parameters['path_or_buf'] = path_

        df.to_csv(**parameters)


    def load(self, df):
        """
            Insert pandas.DataFrame into STORAGE like MySQL, Oracle, ...

            Parameters
            ----------
            df : <DataFrame>

            Note
            ----
            After you add new storage engine,
            also add branch of new one.
        """

        if self.storage_type == "MySQL":
            engine_str = (self.parser_storage.get(self.storage_section, 'ID'),
                          self.parser_storage.get(self.storage_section, 'PWD'),
                          self.parser_storage.get(self.storage_section, 'HOST'),
                          self.parser_storage.get(self.storage_section, 'PORT'),
                          self.parser_storage.get(self.storage_section, 'DB'))
            self.load_db(df, engine_str)
        elif self.storage_type == "Oracle":
            engine_str = (self.parser_storage.get(self.storage_section, 'ID'),
                          self.parser_storage.get(self.storage_section, 'PWD'),
                          self.parser_storage.get(self.storage_section, 'HOST'),
                          self.parser_storage.get(self.storage_section, 'PORT'),
                          self.parser_storage.get(self.storage_section, 'SID'))
            self.load_db(df, engine_str)
        elif self.storage_type == "File":
            self.load_file(df)
        else:
            print "Wrong STORAGE info on config file"
            sys.exit()


    def aggregate(self, path):
        """
            Load file as pandas.DataFrame on specified path
            and aggregate it.

            Parameters
            ----------
            path : <string>
                data file path

            Return
            ------
            <DataFrame>
            Aggregated DataFrame
        """
        try:
            data = pd.DataFrame.from_csv(path, sep=self.sep, index_col=None)
            __LOG__.Trace("Load csv success : %s" % data)
            #data['date'] = data['date'].apply(dateutil.parser.parse, dayfirst=True)
            return data.groupby(self.cols_groupby, as_index=False).agg(self.agg)
        except Exception, ex:
            __LOG__.Trace("Oops: %s" % ex)
            __LOG__.Trace("cols_groupby : %s" % self.cols_groupby)
            __LOG__.Trace("self.agg : %s" % self.agg)

    def run(self):
        while G_SHUTDOWN:
            stdin = sys.stdin.readline().strip()
            __LOG__.Trace("STD IN : %s" % stdin)
            try:
                prefix, path = stdin.split('://')
            except:
                __LOG__.Trace("Wrong stdin come in")
                sys.stderr.write('\n')
                sys.stderr.flush()
                continue
            if prefix == 'file':
                result = self.aggregate(path)
                __LOG__.Trace("Aggregation success : %s" % path)
                self.load(result)
        sys.stderr.write('\n')
        sys.stderr.flush()

def main():
    if len(sys.argv) != 3:
        print 'Usage : %s <Section> <ConfigFilePath>' % sys.argv[0]
        sys.exit()

    obj = Aggregator(*sys.argv)
    __LOG__.Trace("---------------%s Aggregator Start!--------------" % sys.argv[1])

    obj.run()

if __name__ == '__main__':
    main()

