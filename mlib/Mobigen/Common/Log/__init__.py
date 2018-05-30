# -*- coding: cp949 -*-
import sys 
import types
from traceback   import *

from DummyLog    import CDummyLog
from StandardLog import CStandardLog
from StandardErrorLog import CStandardErrorLog
from RotatingLog import CRotatingLog
from PipeLog     import CPipeLog
from UDPLog      import CUDPLog

__VERSION__ = "Release 2 (2005/10/21)"
# pysco.full() ��忡�� ���� �����ϵ��� ����.
#__VERSION__ = "Release 1 (2005/10/11)"
# pysco �浹���� �ذ�
__LOG__ = None

#def Init(**args) :
def Init(userDefine = None) :
	# ��� Import ������ �����Ѵ�.

	impStepList = extract_stack()
	if(len(impStepList)==0) :
		# psyco.full()�� �����ϴ°ɷ� ����.
		import psyco
		frame = psyco._getemulframe()
		impStepList = frame.f_code.co_names

	# __main__ �� �ƴ� ������ import �Ǵ°�� __LOG__ ����� ���� 
	# �ӽ÷� Dummy Log �� �����Ѵ�.

	if(len(impStepList)!=2) :
		curModule = __GetParentModule__()
		if(curModule==None) :
			sys.modules['__main__'].__dict__["__LOG__"] = CDummyLog()
			return

		if(curModule.__name__ != "__main__" and not curModule.__dict__.has_key("__LOG__")) :
			curModule.__dict__["__LOG__"] = CDummyLog()
			return 

	# __LOG__ �� �����Ѵ�.
	global __LOG__

	if(userDefine != None) : __LOG__ = userDefine
	else : 	__LOG__ = __InitMain__()


	sys.modules["__main__"].__LOG__ = __LOG__

	for subModuleName in  sys.modules :
		subModule = sys.modules[subModuleName]

		if(type(subModule) == types.NoneType) : continue
		if(not "Log" in subModule.__dict__) : continue
		if(subModuleName == "__main__") : continue

		# ���� ��⿡�� ��� �����ϵ��� __LOG__ ����Ѵ�.
		subModule.__LOG__ = __LOG__

def __Exception__(type, value, tb):
	if hasattr(sys, 'ps1') or not sys.stderr.isatty() or type == SyntaxError: 
		sys.__excepthook__(type, value, tb)
	else:
		if(__LOG__) :
			 __LOG__.PrintException(type, value, tb)

def AutoException() :
	if __debug__:
		sys.excepthook = __Exception__

def SetLevel(level) :
	global __LOG__
	if(__LOG__) : __LOG__.SetLevel(level)

def __InitMain__() :
	return CStandardLog()

def __GetParentModule__(Test = 0) :

	# impStepList[0] : __GetParentModlue__ �� ȣ���� �Լ�
	# impStepList[1] : Log.py 
	# impStepList[2] : Log.py�� Import �� modlue
	try : 
		impStepList = extract_stack()
		impStepList.reverse()
		parentModulePath = impStepList[2][0]
	except :
		import psyco
		frame = psyco._getemulframe(2)
		parentModulePath = frame.f_code.co_filename

	parentModule = None
	for name in  sys.modules :
		moduleInfo = str(sys.modules[name])
		if (moduleInfo.find(parentModulePath) != -1) : 
			parentModule = sys.modules[name] # ���� ��� ȹ��
			break
		elif (moduleInfo.find("__main__") != -1 and \
			moduleInfo.find("<frozen>") != -1) :
			# freeze�� �������Ѱ��...
			parentModule = sys.modules[name] # ���� ��� ȹ��
			break

	return parentModule

def Version() :
	return __VERSION__ 
