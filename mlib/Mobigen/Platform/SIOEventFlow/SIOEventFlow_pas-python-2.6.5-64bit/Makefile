# Makefile generated by freeze.py script

AR=ar
ASDLGEN=$(srcdir)/Parser/asdl_c.py
ASDLGEN_FILES=$(srcdir)/Parser/asdl.py $(srcdir)/Parser/asdl_c.py
AST_ASDL=$(srcdir)/Parser/Python.asdl
AST_C=$(AST_C_DIR)/Python-ast.c
AST_C_DIR=$(srcdir)/Python
AST_H=$(AST_H_DIR)/Python-ast.h
AST_H_DIR=$(srcdir)/Include
BASECFLAGS=-fno-strict-aliasing
BASEMODLIBS=
BINDIR=$(exec_prefix)/bin
BINLIBDEST=$(LIBDIR)/python$(VERSION)
BLDLIBRARY=$(LDLIBRARY)
BLDSHARED=$(CC) -shared
BUILDEXE=
BUILDPYTHON=python$(BUILDEXE)
CC=gcc -pthread
CCSHARED=-fPIC
CFLAGS=$(OPT)
CFLAGSFORSHARED=
CONFIGFILES=configure configure.in acconfig.h pyconfig.h.in Makefile.pre.in
CONFIG_ARGS='--prefix=/home/pas/user/dhkim'
CONFINCLUDEDIR=$(exec_prefix)/include
CONFINCLUDEPY=$(CONFINCLUDEDIR)/python$(VERSION)
COREPYTHONPATH=$(DESTPATH)$(SITEPATH)$(TESTPATH)$(MACHDEPPATH)$(EXTRAMACHDEPPATH)$(TKPATH)$(OLDPATH)
CPPFLAGS=-I/home/pas/user/dhkim/include/python2.6 -I/home/pas/user/dhkim/include/python2.6
CXX=g++ -pthread
DESTDIRS=$(exec_prefix) $(LIBDIR) $(BINLIBDEST) $(DESTSHARED)
DESTLIB=$(LIBDEST)
DESTPATH=
DESTSHARED=$(BINLIBDEST)/lib-dynload
DIRMODE=755
DIST=$(DISTFILES) $(DISTDIRS)
DISTDIRS=$(SUBDIRS) $(SUBDIRSTOO) Ext-dummy
DISTFILES=README ChangeLog $(CONFIGFILES)
DLINCLDIR=.
DLLLIBRARY=
DYNLOADFILE=dynload_shlib.o
EXE=
EXEMODE=755
EXTRAMACHDEPPATH=
EXTRAPLATDIR=
FILEMODE=644
GLHACK=-Dclear=__GLclear
GRAMMAR_C=$(srcdir)/Python/graminit.c
GRAMMAR_H=$(srcdir)/Include/graminit.h
GRAMMAR_INPUT=$(srcdir)/Grammar/Grammar
INCLDIRSTOMAKE=$(INCLUDEDIR) $(CONFINCLUDEDIR) $(INCLUDEPY) $(CONFINCLUDEPY)
INCLUDEDIR=${prefix}/include
INCLUDEPY=$(INCLUDEDIR)/python$(VERSION)
INSTALL=/usr/bin/install -c
INSTALL_DATA=${INSTALL} -m 644
INSTALL_PROGRAM=${INSTALL}
INSTALL_SCRIPT=${INSTALL}
INSTALL_SHARED=${INSTALL} -m 555
INSTSONAME=$(LDLIBRARY)
LDFLAGS=
LDLAST=
LDLIBRARY=libpython$(VERSION).a
LDLIBRARYDIR=
LDSHARED=$(CC) -shared
LIBC=
LIBDEST=$(SCRIPTDIR)/python$(VERSION)
LIBDIR=$(exec_prefix)/lib
LIBM=-lm
LIBOBJDIR=Python/
LIBOBJS=
LIBP=$(LIBDIR)/python$(VERSION)
LIBPL=$(LIBP)/config
LIBRARY=libpython$(VERSION).a
LIBRARY_OBJS=Modules/getbuildinfo.o 		$(PARSER_OBJS) 		$(OBJECT_OBJS) 		$(PYTHON_OBJS) 		$(MODULE_OBJS) 		$(SIGNAL_OBJS) 		$(MODOBJS)
LIBS=-lpthread -ldl  -lutil
LIBSUBDIRS=lib-tk site-packages test test/output test/data 		test/decimaltestdata 		encodings compiler hotshot 		email email/mime email/test email/test/data 		json json/tests 		sqlite3 sqlite3/test 		logging bsddb bsddb/test csv wsgiref 		lib2to3 lib2to3/fixes lib2to3/pgen2 lib2to3/tests 		ctypes ctypes/test ctypes/macholib idlelib idlelib/Icons 		distutils distutils/command distutils/tests $(XMLLIBSUBDIRS) 		multiprocessing multiprocessing/dummy 		lib-old 		curses $(MACHDEPS)
LINKCC=$(PURIFY) $(MAINCC)
LINKFORSHARED=-Xlinker -export-dynamic
LN=ln
LOCALMODLIBS=
MACHDEP=linux2
MACHDEPPATH=:plat-$(MACHDEP)
MACHDEPS=$(PLATDIR) $(EXTRAPLATDIR)
MACHDEP_OBJS=
MACHDESTLIB=$(BINLIBDEST)
MACOSX_DEPLOYMENT_TARGET=
MAINCC=$(CC)
MAKESETUP=$(srcdir)/Modules/makesetup
MANDIR=${datarootdir}/man
MEMTESTOPTS=$(QUICKTESTOPTS) -x test_dl test___all__ test_fork1 		test_longexp
MODLIBS=$(LOCALMODLIBS) $(BASEMODLIBS)
MODOBJS=Modules/threadmodule.o  Modules/signalmodule.o  Modules/posixmodule.o  Modules/errnomodule.o  Modules/pwdmodule.o  Modules/_sre.o  Modules/_codecsmodule.o  Modules/zipimport.o  Modules/symtablemodule.o  Modules/xxsubtype.o
MODULE_OBJS=Modules/config.o 		Modules/getpath.o 		Modules/main.o 		Modules/gcmodule.o
OBJECT_OBJS=Objects/abstract.o 		Objects/boolobject.o 		Objects/bufferobject.o 		Objects/bytes_methods.o 		Objects/bytearrayobject.o 		Objects/cellobject.o 		Objects/classobject.o 		Objects/cobject.o 		Objects/codeobject.o 		Objects/complexobject.o 		Objects/descrobject.o 		Objects/enumobject.o 		Objects/exceptions.o 		Objects/genobject.o 		Objects/fileobject.o 		Objects/floatobject.o 		Objects/frameobject.o 		Objects/funcobject.o 		Objects/intobject.o 		Objects/iterobject.o 		Objects/listobject.o 		Objects/longobject.o 		Objects/dictobject.o 		Objects/methodobject.o 		Objects/moduleobject.o 		Objects/object.o 		Objects/obmalloc.o 		Objects/rangeobject.o 		Objects/setobject.o 		Objects/sliceobject.o 		Objects/stringobject.o 		Objects/structseq.o 		Objects/tupleobject.o 		Objects/typeobject.o 		Objects/weakrefobject.o 		$(UNICODE_OBJS)
OLDPATH=:lib-old
OPT=-DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes
OTHER_LIBTOOL_OPT=
PARSER_HEADERS=Parser/parser.h 		Parser/tokenizer.h
PARSER_OBJS=$(POBJS) Parser/myreadline.o Parser/tokenizer.o
PGEN=Parser/pgen$(EXE)
PGENOBJS=$(PGENMAIN) $(POBJS) $(PGOBJS)
PGOBJS=Objects/obmalloc.o 		Python/mysnprintf.o 		Parser/tokenizer_pgen.o 		Parser/printgrammar.o 		Parser/pgenmain.o
PLATDIR=plat-$(MACHDEP)
PLATMACDIRS=plat-mac plat-mac/Carbon plat-mac/lib-scriptpackages 	plat-mac/lib-scriptpackages/_builtinSuites 	plat-mac/lib-scriptpackages/CodeWarrior 	plat-mac/lib-scriptpackages/Explorer 	plat-mac/lib-scriptpackages/Finder 	plat-mac/lib-scriptpackages/Netscape 	plat-mac/lib-scriptpackages/StdSuites 	plat-mac/lib-scriptpackages/SystemEvents 	plat-mac/lib-scriptpackages/Terminal
PLATMACPATH=:plat-mac:plat-mac/lib-scriptpackages
POBJS=Parser/acceler.o 		Parser/grammar1.o 		Parser/listnode.o 		Parser/node.o 		Parser/parser.o 		Parser/parsetok.o 		Parser/bitset.o 		Parser/metagrammar.o 		Parser/firstsets.o 		Parser/grammar.o 		Parser/pgen.o
PROFILE_TASK=$(srcdir)/Tools/pybench/pybench.py -n 2 --with-gc --with-syscheck
PYTHON=python$(EXE)
PYTHONFRAMEWORK=
PYTHONFRAMEWORKDIR=no-framework
PYTHONFRAMEWORKINSTALLDIR=
PYTHONFRAMEWORKPREFIX=
PYTHONPATH=$(COREPYTHONPATH)
PYTHON_HEADERS=Include/Python-ast.h 		Include/Python.h 		Include/abstract.h 		Include/asdl.h 		Include/ast.h 		Include/bitset.h 		Include/boolobject.h 		Include/bytearrayobject.h 		Include/bytes_methods.h 		Include/bytesobject.h 		Include/bufferobject.h 		Include/cellobject.h 		Include/ceval.h 		Include/classobject.h 		Include/cobject.h 		Include/code.h 		Include/codecs.h 		Include/compile.h 		Include/complexobject.h 		Include/descrobject.h 		Include/dictobject.h 		Include/enumobject.h 		Include/errcode.h 		Include/eval.h 		Include/fileobject.h 		Include/floatobject.h 		Include/frameobject.h 		Include/funcobject.h 		Include/genobject.h 		Include/import.h 		Include/intobject.h 		Include/intrcheck.h 		Include/iterobject.h 		Include/listobject.h 		Include/longintrepr.h 		Include/longobject.h 		Include/marshal.h 		Include/metagrammar.h 		Include/methodobject.h 		Include/modsupport.h 		Include/moduleobject.h 		Include/node.h 		Include/object.h 		Include/objimpl.h 		Include/opcode.h 		Include/osdefs.h 		Include/parsetok.h 		Include/patchlevel.h 		Include/pgen.h 		Include/pgenheaders.h 		Include/pyarena.h 		Include/pydebug.h 		Include/pyerrors.h 		Include/pyfpe.h 		Include/pymath.h 		Include/pygetopt.h 		Include/pymem.h 		Include/pyport.h 		Include/pystate.h 		Include/pystrcmp.h 		Include/pystrtod.h 		Include/pythonrun.h 		Include/pythread.h 		Include/rangeobject.h 		Include/setobject.h 		Include/sliceobject.h 		Include/stringobject.h 		Include/structmember.h 		Include/structseq.h 		Include/symtable.h 		Include/sysmodule.h 		Include/traceback.h 		Include/tupleobject.h 		Include/ucnhash.h 		Include/unicodeobject.h 		Include/warnings.h 		Include/weakrefobject.h 		pyconfig.h 		$(PARSER_HEADERS)
PYTHON_OBJS=Python/_warnings.o 		Python/Python-ast.o 		Python/asdl.o 		Python/ast.o 		Python/bltinmodule.o 		Python/ceval.o 		Python/compile.o 		Python/codecs.o 		Python/errors.o 		Python/frozen.o 		Python/frozenmain.o 		Python/future.o 		Python/getargs.o 		Python/getcompiler.o 		Python/getcopyright.o 		Python/getmtime.o 		Python/getplatform.o 		Python/getversion.o 		Python/graminit.o 		Python/import.o 		Python/importdl.o 		Python/marshal.o 		Python/modsupport.o 		Python/mystrtoul.o 		Python/mysnprintf.o 		Python/peephole.o 		Python/pyarena.o 		Python/pyfpe.o 		Python/pymath.o 		Python/pystate.o 		Python/pythonrun.o 		Python/structmember.o 		Python/symtable.o 		Python/sysmodule.o 		Python/traceback.o 		Python/getopt.o 		Python/pystrcmp.o 		Python/pystrtod.o 		Python/formatter_unicode.o 		Python/formatter_string.o 		Python/$(DYNLOADFILE) 		$(LIBOBJS) 		$(MACHDEP_OBJS) 		$(THREADOBJ)
PY_CFLAGS=$(CFLAGS) $(CPPFLAGS) $(CFLAGSFORSHARED) -DPy_BUILD_CORE
QUICKTESTOPTS=$(TESTOPTS) -x test_thread test_signal test_strftime 		test_unicodedata test_re test_sre test_select test_poll 		test_linuxaudiodev test_struct test_sunaudiodev test_zlib
RANLIB=ranlib
RESSRCDIR=Mac/Resources/framework
RUNSHARED=
SCRIPTDIR=$(prefix)/lib
SGI_ABI=
SHELL=/bin/sh
SHLIBS=$(LIBS)
SIGNAL_OBJS=
SITEPATH=
SO=.so
SRCDIRS=Parser Grammar Objects Python Modules Mac
STRINGLIB_HEADERS=$(srcdir)/Include/bytes_methods.h 		$(srcdir)/Objects/stringlib/count.h 		$(srcdir)/Objects/stringlib/ctype.h 		$(srcdir)/Objects/stringlib/fastsearch.h 		$(srcdir)/Objects/stringlib/find.h 		$(srcdir)/Objects/stringlib/formatter.h 		$(srcdir)/Objects/stringlib/partition.h 		$(srcdir)/Objects/stringlib/stringdefs.h 		$(srcdir)/Objects/stringlib/string_format.h 		$(srcdir)/Objects/stringlib/transmogrify.h 		$(srcdir)/Objects/stringlib/unicodedefs.h 		$(srcdir)/Objects/stringlib/localeutil.h
SUBDIRSTOO=Include Lib Misc Demo
SVNVERSION=svnversion $(srcdir)
SYSLIBS=$(LIBM) $(LIBC)
TESTOPTS=-l $(EXTRATESTOPTS)
TESTPATH=
TESTPROG=$(srcdir)/Lib/test/regrtest.py
TESTPYTHON=$(RUNSHARED) ./$(BUILDPYTHON) -E -tt
THREADOBJ=Python/thread.o
TKPATH=:lib-tk
UNICODE_OBJS=Objects/unicodeobject.o Objects/unicodectype.o
UNIVERSALSDK=
VERSION=2.6
XMLLIBSUBDIRS=xml xml/dom xml/etree xml/parsers xml/sax
datarootdir=${prefix}/share
exec_prefix=${prefix}
prefix=/home/pas/user/dhkim
srcdir=.

all: SIOEventFlow

config.o: config.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c config.c
frozen.o: frozen.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c frozen.c
M_BaseHTTPServer.o: M_BaseHTTPServer.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_BaseHTTPServer.c
M_ConfigParser.o: M_ConfigParser.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_ConfigParser.c
M_FixTk.o: M_FixTk.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_FixTk.c
M_Mobigen.o: M_Mobigen.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Mobigen.c
M_Mobigen__Common.o: M_Mobigen__Common.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Mobigen__Common.c
M_Mobigen__Common__Log.o: M_Mobigen__Common__Log.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Mobigen__Common__Log.c
M_Mobigen__Common__Log__DummyLog.o: M_Mobigen__Common__Log__DummyLog.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Mobigen__Common__Log__DummyLog.c
M_Mobigen__Common__Log__PipeLog.o: M_Mobigen__Common__Log__PipeLog.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Mobigen__Common__Log__PipeLog.c
M_Mobigen__Common__Log__RotatingLog.o: M_Mobigen__Common__Log__RotatingLog.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Mobigen__Common__Log__RotatingLog.c
M_Mobigen__Common__Log__StandardErrorLog.o: M_Mobigen__Common__Log__StandardErrorLog.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Mobigen__Common__Log__StandardErrorLog.c
M_Mobigen__Common__Log__StandardLog.o: M_Mobigen__Common__Log__StandardLog.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Mobigen__Common__Log__StandardLog.c
M_Mobigen__Common__Log__UDPLog.o: M_Mobigen__Common__Log__UDPLog.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Mobigen__Common__Log__UDPLog.c
M_SocketServer.o: M_SocketServer.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_SocketServer.c
M_StringIO.o: M_StringIO.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_StringIO.c
M_Tkconstants.o: M_Tkconstants.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Tkconstants.c
M_Tkinter.o: M_Tkinter.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_Tkinter.c
M_UserDict.o: M_UserDict.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_UserDict.c
M___future__.o: M___future__.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M___future__.c
M___main__.o: M___main__.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M___main__.c
M__abcoll.o: M__abcoll.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M__abcoll.c
M__threading_local.o: M__threading_local.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M__threading_local.c
M_abc.o: M_abc.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_abc.c
M_atexit.o: M_atexit.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_atexit.c
M_base64.o: M_base64.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_base64.c
M_bdb.o: M_bdb.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_bdb.c
M_bisect.o: M_bisect.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_bisect.c
M_cmd.o: M_cmd.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_cmd.c
M_codecs.o: M_codecs.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_codecs.c
M_collections.o: M_collections.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_collections.c
M_copy.o: M_copy.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_copy.c
M_copy_reg.o: M_copy_reg.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_copy_reg.c
M_ctypes.o: M_ctypes.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_ctypes.c
M_ctypes___endian.o: M_ctypes___endian.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_ctypes___endian.c
M_difflib.o: M_difflib.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_difflib.c
M_dis.o: M_dis.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_dis.c
M_distutils.o: M_distutils.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_distutils.c
M_distutils__dep_util.o: M_distutils__dep_util.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_distutils__dep_util.c
M_distutils__errors.o: M_distutils__errors.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_distutils__errors.c
M_distutils__log.o: M_distutils__log.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_distutils__log.c
M_distutils__spawn.o: M_distutils__spawn.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_distutils__spawn.c
M_distutils__sysconfig.o: M_distutils__sysconfig.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_distutils__sysconfig.c
M_distutils__text_file.o: M_distutils__text_file.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_distutils__text_file.c
M_distutils__util.o: M_distutils__util.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_distutils__util.c
M_doctest.o: M_doctest.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_doctest.c
M_dummy_thread.o: M_dummy_thread.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_dummy_thread.c
M_dummy_threading.o: M_dummy_threading.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_dummy_threading.c
M_email.o: M_email.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email.c
M_email___parseaddr.o: M_email___parseaddr.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email___parseaddr.c
M_email__base64mime.o: M_email__base64mime.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__base64mime.c
M_email__charset.o: M_email__charset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__charset.c
M_email__encoders.o: M_email__encoders.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__encoders.c
M_email__errors.o: M_email__errors.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__errors.c
M_email__feedparser.o: M_email__feedparser.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__feedparser.c
M_email__generator.o: M_email__generator.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__generator.c
M_email__header.o: M_email__header.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__header.c
M_email__iterators.o: M_email__iterators.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__iterators.c
M_email__message.o: M_email__message.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__message.c
M_email__mime.o: M_email__mime.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__mime.c
M_email__parser.o: M_email__parser.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__parser.c
M_email__quoprimime.o: M_email__quoprimime.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__quoprimime.c
M_email__utils.o: M_email__utils.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_email__utils.c
M_encodings.o: M_encodings.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_encodings.c
M_encodings__aliases.o: M_encodings__aliases.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_encodings__aliases.c
M_fnmatch.o: M_fnmatch.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_fnmatch.c
M_formatter.o: M_formatter.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_formatter.c
M_ftplib.o: M_ftplib.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_ftplib.c
M_functools.o: M_functools.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_functools.c
M_genericpath.o: M_genericpath.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_genericpath.c
M_getopt.o: M_getopt.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_getopt.c
M_getpass.o: M_getpass.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_getpass.c
M_gettext.o: M_gettext.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_gettext.c
M_glob.o: M_glob.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_glob.c
M_hashlib.o: M_hashlib.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_hashlib.c
M_heapq.o: M_heapq.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_heapq.c
M_hmac.o: M_hmac.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_hmac.c
M_httplib.o: M_httplib.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_httplib.c
M_inspect.o: M_inspect.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_inspect.c
M_keyword.o: M_keyword.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_keyword.c
M_linecache.o: M_linecache.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_linecache.c
M_locale.o: M_locale.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_locale.c
M_logging.o: M_logging.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_logging.c
M_logging__handlers.o: M_logging__handlers.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_logging__handlers.c
M_macurl2path.o: M_macurl2path.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_macurl2path.c
M_mimetools.o: M_mimetools.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_mimetools.c
M_mimetypes.o: M_mimetypes.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_mimetypes.c
M_ntpath.o: M_ntpath.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_ntpath.c
M_nturl2path.o: M_nturl2path.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_nturl2path.c
M_opcode.o: M_opcode.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_opcode.c
M_optparse.o: M_optparse.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_optparse.c
M_os.o: M_os.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_os.c
M_os2emxpath.o: M_os2emxpath.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_os2emxpath.c
M_pdb.o: M_pdb.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_pdb.c
M_pickle.o: M_pickle.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_pickle.c
M_pkgutil.o: M_pkgutil.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_pkgutil.c
M_posixpath.o: M_posixpath.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_posixpath.c
M_pprint.o: M_pprint.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_pprint.c
M_py_compile.o: M_py_compile.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_py_compile.c
M_pydoc.o: M_pydoc.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_pydoc.c
M_pydoc_topics.o: M_pydoc_topics.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_pydoc_topics.c
M_quopri.o: M_quopri.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_quopri.c
M_random.o: M_random.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_random.c
M_re.o: M_re.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_re.c
M_repr.o: M_repr.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_repr.c
M_rfc822.o: M_rfc822.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_rfc822.c
M_shlex.o: M_shlex.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_shlex.c
M_site.o: M_site.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_site.c
M_smtplib.o: M_smtplib.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_smtplib.c
M_socket.o: M_socket.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_socket.c
M_sre_compile.o: M_sre_compile.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_sre_compile.c
M_sre_constants.o: M_sre_constants.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_sre_constants.c
M_sre_parse.o: M_sre_parse.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_sre_parse.c
M_ssl.o: M_ssl.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_ssl.c
M_stat.o: M_stat.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_stat.c
M_string.o: M_string.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_string.c
M_struct.o: M_struct.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_struct.c
M_subprocess.o: M_subprocess.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_subprocess.c
M_tempfile.o: M_tempfile.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_tempfile.c
M_textwrap.o: M_textwrap.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_textwrap.c
M_threading.o: M_threading.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_threading.c
M_token.o: M_token.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_token.c
M_tokenize.o: M_tokenize.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_tokenize.c
M_traceback.o: M_traceback.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_traceback.c
M_tty.o: M_tty.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_tty.c
M_types.o: M_types.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_types.c
M_unittest.o: M_unittest.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_unittest.c
M_urllib.o: M_urllib.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_urllib.c
M_urlparse.o: M_urlparse.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_urlparse.c
M_uu.o: M_uu.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_uu.c
M_warnings.o: M_warnings.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_warnings.c
M_webbrowser.o: M_webbrowser.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c M_webbrowser.c

SIOEventFlow: config.o frozen.o M_BaseHTTPServer.o M_ConfigParser.o M_FixTk.o M_Mobigen.o M_Mobigen__Common.o M_Mobigen__Common__Log.o M_Mobigen__Common__Log__DummyLog.o M_Mobigen__Common__Log__PipeLog.o M_Mobigen__Common__Log__RotatingLog.o M_Mobigen__Common__Log__StandardErrorLog.o M_Mobigen__Common__Log__StandardLog.o M_Mobigen__Common__Log__UDPLog.o M_SocketServer.o M_StringIO.o M_Tkconstants.o M_Tkinter.o M_UserDict.o M___future__.o M___main__.o M__abcoll.o M__threading_local.o M_abc.o M_atexit.o M_base64.o M_bdb.o M_bisect.o M_cmd.o M_codecs.o M_collections.o M_copy.o M_copy_reg.o M_ctypes.o M_ctypes___endian.o M_difflib.o M_dis.o M_distutils.o M_distutils__dep_util.o M_distutils__errors.o M_distutils__log.o M_distutils__spawn.o M_distutils__sysconfig.o M_distutils__text_file.o M_distutils__util.o M_doctest.o M_dummy_thread.o M_dummy_threading.o M_email.o M_email___parseaddr.o M_email__base64mime.o M_email__charset.o M_email__encoders.o M_email__errors.o M_email__feedparser.o M_email__generator.o M_email__header.o M_email__iterators.o M_email__message.o M_email__mime.o M_email__parser.o M_email__quoprimime.o M_email__utils.o M_encodings.o M_encodings__aliases.o M_fnmatch.o M_formatter.o M_ftplib.o M_functools.o M_genericpath.o M_getopt.o M_getpass.o M_gettext.o M_glob.o M_hashlib.o M_heapq.o M_hmac.o M_httplib.o M_inspect.o M_keyword.o M_linecache.o M_locale.o M_logging.o M_logging__handlers.o M_macurl2path.o M_mimetools.o M_mimetypes.o M_ntpath.o M_nturl2path.o M_opcode.o M_optparse.o M_os.o M_os2emxpath.o M_pdb.o M_pickle.o M_pkgutil.o M_posixpath.o M_pprint.o M_py_compile.o M_pydoc.o M_pydoc_topics.o M_quopri.o M_random.o M_re.o M_repr.o M_rfc822.o M_shlex.o M_site.o M_smtplib.o M_socket.o M_sre_compile.o M_sre_constants.o M_sre_parse.o M_ssl.o M_stat.o M_string.o M_struct.o M_subprocess.o M_tempfile.o M_textwrap.o M_threading.o M_token.o M_tokenize.o M_traceback.o M_tty.o M_types.o M_unittest.o M_urllib.o M_urlparse.o M_uu.o M_warnings.o M_webbrowser.o
	$(LINKCC) $(LDFLAGS) $(LINKFORSHARED) config.o frozen.o M_BaseHTTPServer.o M_ConfigParser.o M_FixTk.o M_Mobigen.o M_Mobigen__Common.o M_Mobigen__Common__Log.o M_Mobigen__Common__Log__DummyLog.o M_Mobigen__Common__Log__PipeLog.o M_Mobigen__Common__Log__RotatingLog.o M_Mobigen__Common__Log__StandardErrorLog.o M_Mobigen__Common__Log__StandardLog.o M_Mobigen__Common__Log__UDPLog.o M_SocketServer.o M_StringIO.o M_Tkconstants.o M_Tkinter.o M_UserDict.o M___future__.o M___main__.o M__abcoll.o M__threading_local.o M_abc.o M_atexit.o M_base64.o M_bdb.o M_bisect.o M_cmd.o M_codecs.o M_collections.o M_copy.o M_copy_reg.o M_ctypes.o M_ctypes___endian.o M_difflib.o M_dis.o M_distutils.o M_distutils__dep_util.o M_distutils__errors.o M_distutils__log.o M_distutils__spawn.o M_distutils__sysconfig.o M_distutils__text_file.o M_distutils__util.o M_doctest.o M_dummy_thread.o M_dummy_threading.o M_email.o M_email___parseaddr.o M_email__base64mime.o M_email__charset.o M_email__encoders.o M_email__errors.o M_email__feedparser.o M_email__generator.o M_email__header.o M_email__iterators.o M_email__message.o M_email__mime.o M_email__parser.o M_email__quoprimime.o M_email__utils.o M_encodings.o M_encodings__aliases.o M_fnmatch.o M_formatter.o M_ftplib.o M_functools.o M_genericpath.o M_getopt.o M_getpass.o M_gettext.o M_glob.o M_hashlib.o M_heapq.o M_hmac.o M_httplib.o M_inspect.o M_keyword.o M_linecache.o M_locale.o M_logging.o M_logging__handlers.o M_macurl2path.o M_mimetools.o M_mimetypes.o M_ntpath.o M_nturl2path.o M_opcode.o M_optparse.o M_os.o M_os2emxpath.o M_pdb.o M_pickle.o M_pkgutil.o M_posixpath.o M_pprint.o M_py_compile.o M_pydoc.o M_pydoc_topics.o M_quopri.o M_random.o M_re.o M_repr.o M_rfc822.o M_shlex.o M_site.o M_smtplib.o M_socket.o M_sre_compile.o M_sre_constants.o M_sre_parse.o M_ssl.o M_stat.o M_string.o M_struct.o M_subprocess.o M_tempfile.o M_textwrap.o M_threading.o M_token.o M_tokenize.o M_traceback.o M_tty.o M_types.o M_unittest.o M_urllib.o M_urlparse.o M_uu.o M_warnings.o M_webbrowser.o /home/pas/user/dhkim/lib/python2.6/config/libpython$(VERSION).a $(MODLIBS) $(LIBS) $(SYSLIBS) -o SIOEventFlow $(LDLAST)

clean:
	-rm -f *.o SIOEventFlow
