# -*- coding: cp949 -*-

# �ڵ����� ����� ���� ��� ����Ʈ

import glob
import os.path

def __RemoveFile__(pat) :
	fileList = glob.glob(pat)
	for file in fileList :
		os.unlink(file)

def __CleanPackage__(path=None) :
	if(path==None) :
		path = os.path.dirname(__file__)

	fileList = glob.glob(path+"/*")
	for file in fileList :
		if os.path.isdir(file) :
			__CleanPackage__(file)

	__RemoveFile__(path+"/*.pyc")
	__RemoveFile__(path+"/*.pyo")
	__RemoveFile__(path+"/.*swp")
