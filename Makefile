# Makefile for mcmas+
# --------------------------------------------------
ifneq (,$(findstring Linux, $(shell uname -s)))
	MCMASEXE = mcmas
	OSTYPE = linux
endif
ifneq (,$(findstring SunOS, $(shell uname -s)))
	MCMASEXE = mcmas
	OSTYPE = solaris
endif
ifneq (,$(findstring CYGWIN, $(shell uname -s)))
	MCMASEXE = mcmas.exe
	OSTYPE = cygwin
endif
ifneq (,$(findstring Darwin, $(shell uname -s)))
	#ifneq (,$(findstring 10.0.0, $(shell uname -r)))
	ifneq (,$(findstring 9, $(shell uname -r | sed 's/\([0-9]*\).*/\1/')))
		OSTYPE = macosx
	else
		OSTYPE = macosx64
	endif
endif

ifneq (,$(findstring x86_64, $(shell uname -m)))
	MCMASEXE = mcmas
	ARCH = x86_64
endif
ifneq (,$(findstring ia64, $(shell uname -m)))
	MCMASEXE = mcmas
	ARCH = ia64
endif

# Cudd Directory
CUDD	= cudd-2.4.2-exp/

# ---- COMPILERS ----
# C++ compiler
CPP     = g++
# C compiler
CC 	= gcc
# CC compilation flags
CCFLAGS	= -O3
# CPP compilation flags
CPPFLAGS = -O3 -W 
INCLUDE = -Iinclude -I$(CUDD)include #-I$(CUDD)obj
# ---- END COMPILERS ----

GCC_MAJOR := $(shell (echo|gcc -dM -E -|grep __GNUC__|cut -d' ' -f3))
GCC_MINOR := $(shell (echo|gcc -dM -E -|grep __GNUC_MINOR__|cut -d' ' -f3))
GCC_PATCHLEVEL := $(shell (echo|gcc -dM -E -|grep __GNUC_PATCHLEVEL__|cut -d' ' -f3))

ifeq ($(shell if [ $(GCC_MAJOR) -lt 4 ]; then echo T; else echo F; fi), T)
	CUDD_MAKEFILE = Makefile.linux64
	#echo GCC version too old
else
	ifeq ($(shell if [ $(GCC_MAJOR) -eq 4 ]; then echo T; else echo F; fi), T)
		ifeq ($(shell if [ $(GCC_MINOR) -lt 2 ]; then echo T; else echo F; fi), T)
			CUDD_MAKEFILE = Makefile.linux64
		else
			ifeq ($(shell if [ $(GCC_MINOR) -eq 2 ]; then echo T; else echo F; fi), T)
				ifeq ($(shell if [ $(GCC_PATCHLEVEL) -lt 4 ]; then echo T; else echo F; fi), T)
					CUDD_MAKEFILE = Makefile.linux64
				else
					CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4
				endif
			else
				CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4	
			endif
		endif
	else
		CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4	
	endif
endif

ifeq ($(OSTYPE),linux)
	ifeq ($(ARCH),ia64)
		CUDD_MAKEFILE = Makefile.linux64
	else
		ifeq ($(ARCH),x86_64)
			ifeq ($(shell if [ $(GCC_MAJOR) -lt 4 ]; then echo T; else echo F; fi), T)
				CUDD_MAKEFILE = Makefile.linux64
			else
				ifeq ($(shell if [ $(GCC_MAJOR) -eq 4 ]; then echo T; else echo F; fi), T)
					ifeq ($(shell if [ $(GCC_MINOR) -lt 2 ]; then echo T; else echo F; fi), T)
						CUDD_MAKEFILE = Makefile.linux64
					else
						ifeq ($(shell if [ $(GCC_MINOR) -eq 2 ]; then echo T; else echo F; fi), T)
							ifeq ($(shell if [ $(GCC_PATCHLEVEL) -lt 4 ]; then echo T; else echo F; fi), T)
								CUDD_MAKEFILE = Makefile.linux64
							else
								CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4
							endif
						else
							CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4	
						endif
					endif
				else
					CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4	
				endif
			endif

		else
			CUDD_MAKEFILE = Makefile.linux
		endif
	endif
endif
# Solaris
ifeq ($(OSTYPE),solaris)
	CUDD_MAKEFILE = Makefile.solaris
endif
# Cygwin
ifeq ($(OSTYPE),cygwin)
  ifeq ($(ARCH),x86_64)
    CUDD_MAKEFILE = Makefile.cygwin64
  else
    CUDD_MAKEFILE = Makefile.cygwin
  endif
endif
# Darwin
ifeq ($(OSTYPE),macosx)
	CUDD_MAKEFILE = Makefile.macosx
endif

ifeq ($(OSTYPE),macosx64)
	CUDD_MAKEFILE = Makefile.macosx64
endif



GRAMMAR		= parser/nssis
LEXFILE 	= parser/nssis
DRIVER		= parser/mcmas-driver
SYNTAXCHECK	= parser/syntaxcheck
UTILITIES	= utilities/utilities
TYPES		= utilities/types
SIMULATION	= utilities/simulation
EXPORT_MODEL    = utilities/export_model
MAIN		= main
LEX		= flex
YACC		= bison
############################################################################
# Find which version of Bison is used
BISON_VERSION := $(shell (echo|$(YACC) --version|grep bison|cut -d' ' -f4))
ifeq ($(BISON_VERSION), 2.3)
	BISONSUFFIX =
else
	BISONSUFFIX = _new
endif
############################################################################

CUDDLIBS = $(CUDD)obj/cuddObj.o $(CUDD)obj/libobj.a $(CUDD)cudd/libcudd.a $(CUDD)mtr/libmtr.a $(CUDD)st/libst.a $(CUDD)util/libutil.a $(CUDD)epd/libepd.a

default: all

all: cuddlibrary mcmas

cuddlibrary: 
	cd $(CUDD) && /bin/cp $(CUDD_MAKEFILE) Makefile && $(MAKE)



OBJECTS = $(TYPES).o parser/lex.yy.o $(GRAMMAR).o $(DRIVER).o $(SYNTAXCHECK).o $(UTILITIES).o $(SIMULATION).o $(EXPORT_MODEL).o 

mcmas : $(OBJECTS) $(MAIN).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) $(CUDDLIBS) $(OBJECTS) -o mcmas $(MAIN).cc

parser/lex.yy.o: $(LEXFILE).ll $(GRAMMAR)$(BISONSUFFIX).yy
	$(LEX) -oparser/lex.yy.c $(LEXFILE).ll

	$(YACC) --defines=$(GRAMMAR).hh $(GRAMMAR)$(BISONSUFFIX).yy -o $(GRAMMAR).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE)  -c parser/lex.yy.c -o parser/lex.yy.o

$(GRAMMAR).o: include/utilities.hh include/types.hh $(LEXFILE).ll $(GRAMMAR)$(BISONSUFFIX).yy
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(GRAMMAR).cc -o $(GRAMMAR).o

$(SYNTAXCHECK).o: include/utilities.hh include/types.hh $(SYNTAXCHECK).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(SYNTAXCHECK).cc -o $(SYNTAXCHECK).o

$(UTILITIES).o: include/utilities.hh $(UTILITIES).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(UTILITIES).cc -o $(UTILITIES).o

$(TYPES).o: include/types.hh $(TYPES).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(TYPES).cc -o $(TYPES).o

$(SIMULATION).o: include/utilities.hh include/types.hh $(SIMULATION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(SIMULATION).cc -o $(SIMULATION).o

$(EXPORT_MODEL).o: include/utilities.hh $(EXPORT_MODEL).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(EXPORT_MODEL).cc -o $(EXPORT_MODEL).o

$(DRIVER).o: $(DRIVER).cc 
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(DRIVER).cc -o $(DRIVER).o 

.PHONY : clean
clean: cleancudd cleanmcmas

cleancudd:
	cd $(CUDD) && $(MAKE) clean

cleanmcmas:
	rm $(MCMASEXE) $(OBJECTS) parser/lex.yy.c parser/location.hh parser/position.hh parser/stack.hh $(GRAMMAR).hh $(GRAMMAR).cc 
