#  $Id: Makefile 2013 2000-09-01 21:13:45Z foster $
#
#  $Source$
#
 
#OPT = -O3
#LDFLAGS = -L.:../lib
#LDLIBS = -lone
libs_used = ../lib/libone.a 

INCLUDES = -I. -I../Include -I-

###########################################################################
#
#			TARGETS
#

testing: test 

test: two

two:
	mkdir two

# by using "none" the library won't be automatically made by rules_for_makefile
dir_name = none
# by defining sub_dir, it will build Include/two/*.h
sub_dir = two

install: ../lib/lib$(sub_dir).a 

local: local_library.a

clean: 
	-../rmo

############################################################################
#
#                      LEVELIZATION
#

level_0 = foo.o
level_1 = bar.o
level_2 = 
level_3 = 
level_4 = 
level_5 =
level_6 =
level_7 =
level_8 =

# ... up to level 25 allowed by default.  After that you have to modify ../rules_for_makefile


# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #
#									  #
# Every file/class must appear on the above list somewhere.		  #
# If you don't want to use the built levilization, then put 		  #
# everything as level zero and then list them explicitely.                #
# I.e.									  #
#									  #
#	level_0 = foo.o bar.o ...					  #
#	foo.test.executable: bar.o					  #
#									  #
# Should you write non-levelized code, you will have to list 		  #
# dependences explicitely.  I.e.					  #
#									  #
#	level_0 = foo.o bar.o ...					  #
#	foo.test.executable: bar.o					  #
#	bar.test.executable: foo.o					  #
#									  #
# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #

############################################################################
#
#            INCLUDING OUR RULES AND DEFINITIONS
#
#

include ../rules_for_makefiles


