#!/usr/bin/python
# -*- coding: cp949 -*-

# V1.0 : 060706 : seory
# V1.1 : 060727 : tesse
# V1.2 : 061009 : seory : info���� ó���� ���� option : def getInfo ���� 
# V1.3 : 061023 : eek   : info���Ͽ� ������ ���������ʴ� ��� ���� �����
#                         ������ ã�� ��� �����ϵ��� ����...

import sys, time, os, re, getopt,glob
#from DataContainer import *
import Mobigen.DataProcessing.DataContainer2.DataContainer as DataContainer
from socket import timeout ### for timeout exception

import signal
SHUTDOWN = False
def handler(sigNum, frame) :
	global SHUTDOWN
	SHUTDOWN = True

signal.signal(signal.SIGTERM, handler)
signal.signal(signal.SIGINT, handler)
signal.signal(signal.SIGHUP, handler)
signal.signal(signal.SIGPIPE, handler)

def error(val) :
	try :
		sys.stderr.write( "--- error : %s\n" % val )
		sys.stderr.flush()
	except : pass

def debug(val) :
	try :
		sys.stderr.write( "*** debug : %s\n" % val )
		sys.stderr.flush()
	except : pass

def log(val) :
	try :
		sys.stderr.write( "+++ log   : %s\n" % val )
		sys.stderr.flush()
	except : pass

# STDIN Binary DATA FORMAT : PType 1
# Space(6)length(10)yyyymmddhhmmss(14)OptData(16)Body

def putInfo(fileName, fileTime, recno) :
	fh = open( fileName, 'w')
	fh.write("%s,%s" % (fileTime, recno) )
	fh.close()

def getInfo(fileName) :
	if os.path.exists( fileName ) :
		fh = open( fileName, 'r')
		try :
			fileTime, recno = fh.readline().split(',')
		except : 
			return  '-2', 0
		if re.search('^\s*\d{14}', fileTime) == False :
			# info������ �ִµ� ���Ŀ� ���� �ʴ� ��� : ���� ������ ���Ͽ� ���� ù ��° ���κ��� ����
			return  '-2', 0
		else :
			recno = int(recno)
			fh.close()
			return fileTime, recno
	else :
		# info������ ���� ��� : ���� ������ ���Ͽ� ���� ù ��° ���κ��� ����
		return  '-2', 0

def getOldFile(homeDir, fileName):

	log("getOldFile")

	#oldPath = os.getcwd()
	#os.chdir(homeDir)
					
	nextFile = None

	while True:
		if SHUTDOWN == True :
			log( 'shutdown detected' )
			break
		# YYYYMMDDHHMMSS.db = 14 byte
		fileList = glob.glob( "%s/??????????????.db" % homeDir)
		if (len(fileList) >0) :
			fileList.sort()
			for file in fileList:
				# homedir/YYYYMMDDHHMMSS.db => YYMMDDHHMMSS
				file = file[file.rfind("/")+1:-3]
				log("file[%s]" % file)
				#file = file.strip("*.db")
				if fileName >= file:
					continue
				else:
					nextFile = file
					break
		if nextFile:
			break

		# ������ ���� ���
		log("file not found... sleep(5)")
		time.sleep(5)

	#os.chdir(oldPath)

	return nextFile


def main() :

	try :
		 ### �ڿ� �μ��� �ð�� : ���̰�, �ƴҰ�� �Ⱥ��δ�
		 ### : �� ������� optList �� Ʃ���� ����Ʈ�� ��ȯ�ȴ�.
		optList, args = getopt.getopt(sys.argv[1:], 'p:f:t:w:n:i:d:')
		if len(args) != 2 : raise Exception
		optDict = {}
		for optKey, optVal in optList : optDict[optKey] = optVal
	except :
		print 'usage : %s [-pftwni] homeDir infoFileName' % (sys.argv[0])
		print '		-p[6] : protocol type, default:1'
		print '		-f[okd|kd|d] : okd : message format = option(16byte) key(10byte) data'
		print '						kd : message format = key(10byte) data'
		print '						 d : message format = data'
		print '						   : default format = fileTime(yyyymmddhhmmss) option(16byte) key(10byte) data'
		print '		-t[Num] : read block timeout second, default is 1, for signal process'
		print '		-w[Num] : if no date to read, wait this second, default is 0.1'
		print '		-n[Num] : if no data to read, list up next file for this second interval, default is 10'
		print '		-i[Num] : info file update period record count, default is 10'
		print '		-v[2] : dc version , default is dc2'
		sys.exit()

	if '-p' in optDict : pType = int( optDict['-p'] )
	else : pType = 1

	if '-f' in optDict : fmt = optDict['-f']
	else : fmt = 'tod'

	if '-t' in optDict : readBlockTimeout = int( optDict['-t'] )
	else : readBlockTimeout = 1

	if '-w' in optDict : waitDataSec = int( optDict['-w'] )
	else : waitDataSec = 0.1

	if '-n' in optDict : nextFileCheckSec = int( optDict['-n'] )
	else : nextFileCheckSec = 10

	if '-i' in optDict : infoUpCnt = int( optDict['-i'] )
	else : infoUpCnt = 10

	if '-v' in optDict : version = int( optDict['-v'] )
	else : version = 2

	homeDir = args[0]
	if os.path.exists(homeDir) == False :
		os.mkdir(homeDir)

	db = DataContainer(homeDir, ReadBlockTimeout=readBlockTimeout, \
		WaitDataSec=waitDataSec, NextFileCheckSec=nextFileCheckSec, \
		Version=version)

	infoFileName = "%s/%s" % (homeDir, args[1])

	#sFileTime = None
	sFileTime = '-1'
	sRecno = 0

	skipFlag = True

	try : 
		sFileTime, sRecno = getInfo( infoFileName )
		readFileTmp = '%s/%s.db' % ( homeDir, sFileTime )
		# info���� ������ ��Ȯ�ѵ� ������ ���°�� : 
		# ������ ���������̳� �ϴ� ���������Ϸ� �����ϵ��� : �ڼ������� ��û
		if os.path.exists(readFileTmp) == False :
			if sFileTime != "-1":
				# sFileTime�� -1�� �ƴϰ� ������ ���� ��쿡
				# ���� �ֱ� ������ ��Ÿ�������� ��ٸ�.

				sFileTime = getOldFile(homeDir, sFileTime)
				sRecno = 0
				skipFlag = False
			else:
				sFileTime = '-1'
				sRecno = 0
	except :
		error( "except %s" % sFileTime )
		pass

	log("sFileTime[%s] sRecno[%s]" % (sFileTime, sRecno))
	flagFirst = True
	recCnt = 0

	fileTime, msgTime, opt, key, val = ('', '', '', '', '')

	while True : 
		try :
			if SHUTDOWN == True :
				log( 'shutdown detected' )
				break

			if sFileTime == None:
				log( 'sFileTime is NULL' )
				break

			if flagFirst and sFileTime != None :
				flagFirst = False
				if(sFileTime=="-1") :
					fileTime, msgTime, opt, key, val = db.getLast()
				else :
					fileTime, msgTime, opt, key, val = db.get(sFileTime, sRecno)
					# ĳ���Ǿ��ִ� �����ʹ� ������� �ʱ����ؼ� ������. eek
					if skipFlag:
						continue
			else :
				try :
					fileTime, msgTime, opt, key, val = db.next()
				except timeout :
					continue
				except OSError, err:

					if "Errno 2" in sys.exc_value.__str__() :
						# ���ϻ����� ��� �������ϰ� ���� ����� �̷���
						# ������ ������ ã�Ƽ� ó���ϵ��� ��.
						sFileTime = getOldFile(homeDir, fileTime)
						sRecno = 0
						skipFlag = False
						flagFirst = True
						continue

					raise OSError

			if fmt == 'okd'	:
				data = "%16s%10d%s" % (opt, key, val)

			elif fmt == 'kd':
				data = "%10d%s" % (key, val)

			elif fmt == 'd' :
				data = val

			else :
				data = "%14s%16s%10d%s" % (fileTime, opt, key, val)

			if pType == 6 :
				sys.stdout.write(data + "\n")
				sys.stdout.flush()

			else :
				header = "      %010d" % ( len(data) )
				sys.stdout.write( header + data)
				sys.stdout.flush()

			if recCnt % infoUpCnt == 0 :
				putInfo(infoFileName, fileTime, key)

			infoUpCnt += 1

		except Exception, err :
			if SHUTDOWN == True :
				log( 'shutdown detected' )
			else :
				error( err.__str__() )
			break

	if fileTime != '':
		putInfo(infoFileName, fileTime, key)
	db.close()
	log( 'shutdown' )

if __name__ == "__main__":
	main()

