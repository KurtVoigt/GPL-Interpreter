# Mon Sep 23 20:36:15 PDT 2019

# This Makefile should work for p1 - p6
#
# It makes a couple assumptions:
#
# (1) the name of the directory is the phase name (e.g. p1, p2, etc)
#
# (2) every .cpp file in this directory is part of the gpl project
#     if you want to keep other .cpp files in this directory you will need to
#     replace "C++SRC = $(wildcard *.cpp)" with a list of files of the form
#     "C++SRC = file1.cpp file2.cpp file3.cpp"
#
#

CXX = g++
CPPFLAGS = -std=c++17 -g -MMD 
CPPWARNINGS = -Wall -pedantic

#now unused
KERNEL_NAME := $(shell sh -c 'uname -s 2>/dev/null || echo not')

# assume the current directory is the phase name
#   /home/.../p2   is the directory where you will keep p2
PHASE := $(shell sh -c "basename \"$(PWD)\"")

# set up the command line options to define pre-processor variables
# -DSYM_TAB has same effect of adding "#define SYM_TAB" to .cpp file
# SYM_TAB and GRAPHICS are used by my public code
#   SYM_TAB turns on the symbol_table for p2-p6
#   GRAPHICS turns on graphics for p4-p6
# P3 P4 P5 P6 are used by my private code so I can use the same file for 
#   multiple phases.  You may use them if you want.
ifeq ($(PHASE),p1)
  MACRO_DEFINITIONS = -DP1
else ifeq ($(PHASE),p2)
  MACRO_DEFINITIONS = -DSYM_TAB -DP2
else ifeq ($(PHASE),p3)
  MACRO_DEFINITIONS = -DSYM_TAB -DP3
else ifeq ($(PHASE),p4)
  MACRO_DEFINITIONS = -DSYM_TAB -DGRAPHICS -DP3 -DP4
else ifeq ($(PHASE),p5)
  MACRO_DEFINITIONS = -DSYM_TAB -DGRAPHICS -DP3 -DP4 -DP5
else ifeq ($(PHASE),p6)
  MACRO_DEFINITIONS = -DSYM_TAB -DGRAPHICS -DP3 -DP4 -DP5 -DP6
else
  PHASE = UNKNOWN PHASE: THIS IS AN ERROR (bad directory name, must be p1,p2,...p6)
endif

LIBDIRS  = -L/usr/X11R6/lib
LIBS = -lX11 -lglut -lGL -lGLU -lm

# C++SRC is a list of all .cpp files in current directory
#   assumes every .cpp file in current directory is part of gpl
#   replace $(wildcard *.cpp) with a list of files if you keep 
#   non-gpl .cpp files in this directory
C++SRC = $(wildcard *.cpp)

# create a list of object files by substituting the .cpp in above list with .o
C++OBJ = $(C++SRC:%.cpp=%.o)

# create a list of dependency file (generated with g++ -MMD)
C++DEP = $(C++SRC:%.cpp=%.d)

# compile the gpl executable
# this Makefile depends on the source being in a directory named
#   for the current phase (p1, p2, ..., p6).  It will not work if 
#   it is in a different directory.  PHRASE set to error when the
#   directory is not a legal directory.
gpl: gpl.tab.o lex.yy.o $(C++OBJ)
	@echo "--------------------------------------------------------------------"
	@echo " compiling phase $(PHASE) "
	@echo "--------------------------------------------------------------------"
	$(CXX) -g -o gpl gpl.tab.o lex.yy.o $(C++OBJ) $(LIBDIRS) $(LIBS)

# compiling gpl.cpp is phase dependent (MACRO_DEFINITIONS (defined above) 
# holds the phase dependent macro definitions)
gpl.o: gpl.cpp Makefile gpl.tab.o lex.yy.o
	$(CXX) $(CPPFLAGS) $(CPPWARNINGS) $(MACRO_DEFINITIONS) -c gpl.cpp

gpl.tab.c gpl.tab.h: gpl.y
	bison -vd gpl.y

gpl.tab.o: gpl.y
	bison -vd gpl.y
	$(CXX) $(CPPFLAGS) $(MACRO_DEFINITIONS) -w -c gpl.tab.c

lex.yy.c: gpl.l
	flex gpl.l

lex.yy.o: lex.yy.c gpl.tab.h 
	$(CXX) $(CPPFLAGS) $(MACRO_DEFINITIONS) -c lex.yy.c

# pattern rule to compile all the .cpp files
%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CPPWARNINGS) $(MACRO_DEFINITIONS) -c $< -o $@
	
# include dependency files (.d file) generated by g++
-include $(C++DEP)

clean:
	rm -f $(C++OBJ) $(C++DEP) gpl lex.yy.c lex.yy.o lex.yy.d \
	y.output gpl.tab.h gpl.tab.c gpl.tab.d gpl.tab.o *.gch
	rm -rf results
