#!/bin/env python
#-*- coding:utf-8 -*-

import os
import signal
import sys
import time
import xml.dom.minidom

import API.M6 as M6

import Mobigen.Common.Log as Log;

Log.Init()

TERM = False

def signal_handler(inum, ifrm) :

    __LOG__.Trace("Catch Signal : %s" % inum)
    global TERM
    TERM = True

signal.signal(signal.SIGTERM, signal_handler)
signal.signal(signal.SIGINT , signal_handler)
try :
    signal.signal(signal.SIGHUP , signal_handler)
except :
    pass
try :
    signal.signal(signal.SIGPIPE, signal_handler)
except :
    pass


def shutdown() :
    __LOG__.Trace("Call Shutdown!!")
    os._exit(1)



def pars(ixml) :

    #
    # lsum = [isum, isum, ....]
    #
    # isum = {isnm, conn, list} = "Sum_info"
    #
    # isnm = "Sumname"
    #
    # conn = {host, user, pass} = "Connection"
    #
    # host = "url" -&gt; "ip:port"
    # user = "user"
    # pass = "pass"
    #
    # list = [lque, lque, ....]
    #
    # lque = [ique, ique, ....]
    #
    # ique = {ikey, ival, ipos, irng, isql} = "Query"
    #
    # ikey = "keys"
    # ival = "values"
    # ipos = "pos"
    # irng = "range"
    # isql = <data>
    #

    # type = "HASH_MAIN", "HASH_SUB", "HASH_MAIN", "HASH_SUB"
    #
    # list = [[0que, 1que] , [2que, 3que]]
    #
    # lrec = [ 0que&lt;-1que] + [2que&lt;-3que ]
    #

    lsum = []

    for nsum in xml.dom.minidom.parse(ixml).getElementsByTagName("Sum_info") :

        isum = {}

        isum["sumname"] = str(nsum.getElementsByTagName("Sumname")[0].childNodes[0].data)
        try: suffix = str(nsum.getElementsByTagName("Suffix")[0].childNodes[0].data)
        except: suffix = '0'
        isum["suffix"] = suffix

        ncon = nsum.getElementsByTagName("Connection")[0]

        isum["connection"] = {}

        isum["connection"]["host"] = str(ncon.getAttribute("url" )).split("//")[1]
        isum["connection"]["user"] = str(ncon.getAttribute("user"))
        isum["connection"]["pass"] = str(ncon.getAttribute("pass"))

        isum["querys"] = []

        lque = []

        for nque in nsum.getElementsByTagName("Query") :

            iknd = str(nque.getAttribute("type"  ))
            ikey = str(nque.getAttribute("keys"  ))
            ival = str(nque.getAttribute("values"))
            ipos = str(nque.getAttribute("pos"   ))
            irng = str(nque.getAttribute("partition_range" ))
            ihin = str(nque.getAttribute("hint" ))
            summary_range = str(nque.getAttribute("sum_range" ))

            if iknd in ["UNIQUE", "HASH"]:
                if lque:
                    isum["querys"].append(lque)
                lque = []

            ique = {}

            ique["type"  ] = iknd or "UNIQUE"
            ique["keys"  ] = ikey and [int(i) for i in ikey.split(",")] or []
            ique["values"] = ival and [int(i) for i in ival.split(",")] or []
            ique["pos"   ] = ipos and [int(i) for i in ipos.split(",")] or []
            ique["hint"  ] = ihin
            ique["partition_range" ] = irng or "5"
            ique["summary_range"] = summary_range or "5"

            ique["sql"   ] = str(nque.childNodes[0].data.encode("utf-8"))
            lque.append(ique)

            # for n in nque.childNodes:
            #       if n.data.strip() == '': continue
            #       try :
            #           ique["sql"   ] = str(n.data)
            #       except :
            #           ique["sql"   ] = str(n.data.encode("utf-8"))
            #       lque.append(ique)

        if lque:
            isum["querys"].append(lque)

        lsum.append(isum)

    return lsum

def summ(istm, iptm, isum):

    istm += '00'

    ihst = isum["connection"]["host"]
    iuid = isum["connection"]["user"]
    ipwd = isum["connection"]["pass"]

    conn = M6.Connection(ihst, iuid, ipwd)
    curs = conn.Cursor()

    curs.SetFieldSep ("|^|")
    curs.SetRecordSep("|&amp;|")

    join_hash = {}
    val_length = 0
    lrec = []

    for lque in isum["querys"]:
        ique = lque[0]
        ityp = ique["type"  ]
        ikey = ique["keys"  ]
        ival = ique["values"]
        irng = ique["partition_range" ] + '00'
        ihit = ique["hint"  ]
        isrn = ique["summary_range"] # 분 단위

        if isrn.lower() == "daily":
            st_time = istm[:8] + "000000" # "20180618104800" -> "20180618000000"
        elif isrn.lower() == "hourly":
            st_time = istm[:10] + "0000"
        else: # "20180618104800" -> '20180618100000'
            st_time = time.strftime("%Y%m%d%H%M%S",
                    time.localtime(time.mktime(time.strptime(istm, "%Y%m%d%H%M%S")) - \
                            (int(isrn) * 60)))
            # st_time = stdin들어온 시간 - summary_range

        en_time = istm

        # st_time, en_time 을 partition_range +'00' 자리수만큼 내림
        st_part = str(int(st_time) - (int(st_time) % int(irng)))
        en_part = str(int(en_time) - (int(en_time) % int(irng)))

        condition = "<" if st_part != en_part and en_part == en_time else "<="

        ipar = str(int(istm) - (int(istm) % (int(irng))))

        __LOG__.Trace("%s <= PARTITION AND PARTITION <= %s  where  %s <= TIMESTAMP AND TIMESTAMP <= %s" % (st_part, en_part, st_time, en_time))

        isql = "\n/*+ LOCATION ( '%s' <= PARTITION AND PARTITION %s '%s' %s ) */\n%s" % \
                (st_part, condition, en_part, ihit, ique["sql"])

        isql = isql.replace("%stime", st_time)
        isql = isql.replace("%etime", en_time)
        isql = isql.replace("%pre_stime", iptm)
        isql = isql.replace("%cdate", istm[:8])
        isql = isql.replace("%ctime", istm[8:12])

        __LOG__.Trace(" ** SQL ** %s" % isql)

        #성공할때까지 쿼리 수행 최대 3번
        success_flag = False
        for i in range(3):
            try:
                curs.Execute2(isql)
                lres = [ires for ires in curs]
                success_flag = True
                break
            except:
                __LOG__.Exception()

        if not success_flag:
            continue

        __LOG__.Trace("lres length = %d" % (len(lres)))

        joined_key = dict()

        if ityp == "HASH":
            # join_hash 만들기
            # join_hash = {"key1|^|...|^|keyN": [val1, ... , valM]}
            for row in lres:
                key = "|^|".join([str(row[idx]) for idx in ikey])
                val = [str(row[idx]) for idx in ival]
                try:
                    if not joined_key.has_key(key):
                        join_hash[key].extend(val)
                        joined_key[key] = None
                except:
                    join_hash[key] = [''] * val_length
                    join_hash[key].extend(val)

            val_length += len(ival)
            for key in join_hash:
                if len(join_hash[key]) < val_length:
                    join_hash[key].extend([''] * (val_length - len(join_hash[key])))
        else :
            lrec = lrec + lres

    lrec = lrec + [key.split("|^|") + join_hash[key] for key in join_hash]

    curs.Close()
    conn.close()

    __LOG__.Trace("lrec length = %d" % (len(lrec)))

    return lrec


def loop(lsum, idir) :

    __LOG__.Trace("strt loop...")

    while not TERM :

        try : line = sys.stdin.readline()
        except : break

        if not line : break

        line = line.rstrip()

        __LOG__.Trace("read %s" % (line))

        if not line.startswith("noti://") :
            __LOG__.Trace("Require Prefix 'noti://' : %s" % line)
            sys.stderr.write("%s\n" % line)
            sys.stderr.flush()
            continue

        # stdin으로 들어온 시간 같음
        istm = os.path.basename(line)[:12]

        if not istm.isdigit():

            sys.stderr.write("%s\n" % (line))
            sys.stderr.flush()

            continue

        #일주일 전 시간
        iptm = time.strftime("%Y%m%d%H%M%S", time.localtime(time.mktime(time.strptime(istm, "%Y%m%d%H%M%S")) - 604800))

        #현재 시각
        st_time = time.time()

        for isum in lsum : # xml파싱된 파일
            #현재 시각
            sst_time = time.time()

            isnm = isum["sumname"]
            isuf = isum["suffix"]

            __LOG__.Trace("summ stime : %s  summ name : %s" % (istm, isnm))

            while not TERM :
                try :
                    # istm : xml의 sumname 뭉텅이 하나 대표하는 이름같음
                    # iptm : stdin으로 들어온시간의 일주일전 시간
                    # isum : sumname의 뭉텅이 하나
                    lrec = summ(istm, iptm, isum)
                    break
                except :
                    __LOG__.Exception()
                    time.sleep(1)

            #fime = os.path.join(idir, "%s_%s_%s_%s.dat" % (isnm, istm + "00", len(lrec), os.getpid()))
            fime = os.path.join(idir, "%s-%s-%s.dat" % (isnm, isuf, istm + "00"))

            fd = open(fime, "w")
            for irec in lrec:
                fd.write(",".join([str(i) for i in irec]) + "\n")
            fd.close()

            sys.stdout.write("file://%s\n" % (fime))
            sys.stdout.flush()
            __LOG__.Trace("Std OUT : %s  Processing Time : %.2f" % (fime, (time.time() - sst_time)))

        __LOG__.Trace("Total Processing Time : %.2f" % (time.time() - st_time))

        sys.stderr.write("%s\n" % (line))
        sys.stderr.flush()

    __LOG__.Trace("stop loop...")


def main(args) :

    __LOG__.Trace("strt process")

    ixml, idir = args

    ixml = os.path.expanduser(ixml)
    idir = os.path.expanduser(idir)
    __LOG__.Trace("ixml %s" % (ixml))
    __LOG__.Trace("idir %s" % (idir))

    if not os.path.exists(idir):
        os.makedirs(idir)
    if not os.path.isdir(idir):
        print_function()
        sys.exit()

    loop(pars(ixml), idir)

    __LOG__.Trace("stop process")


def print_usage():
    print >> sys.stderr, "Usage : %s SUMMARY_NAME XML_FILE OUTPUT_DIR" % module
    print >> sys.stderr, "Exam  : %s CDR_SUMMARY_5M ~/SFMILOG/conf/IRIS_XML/CDR_SUMMARY.xml /DATA1/DEV/OUTPUT" % module


if  __name__ == "__main__" :
    module = os.path.basename(sys.argv[0])

    if  len(sys.argv) < 4 :
        print_usage()
        sys.exit()

    log_file = "log/%s_%s.log" % (os.path.basename(sys.argv[0]), sys.argv[1])
    if '-d' in sys.argv:
        Log.Init()
        sys.argv.remove('-d')
    else:
        Log.Init(Log.CRotatingLog(os.path.expanduser(log_file), 10000000, 19))

    try    : main(sys.argv[2: ])
    except : __LOG__.Exception()

