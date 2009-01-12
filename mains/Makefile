#  $Id: Makefile 2024 2000-09-09 15:19:56Z foster $
#
#  $Source$
#

#
#	The assumption of this directory is that each .cc file has
#	a main() defined and that is about it.  So there aren't the 
#	usual .h and .test.cc files.  There shouldn't be any classes
#	defined in this directory.
#
#       To add a new executable:
#
#		1) create a new_main.cc (which has a main() defined in it)
#		2) add new_main to the list of targets defining "all"
#		3) add new_main to .cvsignore
#

INCLUDES = -I. -I../Include -I-

###########################################################################
#
#			TARGETS
#

all: sample

clean: 
	-../rmo

################################################################################
#
#    Definitions of the compiler etc
#

LDFLAGS  = -L../lib
LDLIBS   = -lone -ltwo 
INCLUDES = -I../Include 
CC       = g++ $(INCLUDES) $(LDFLAGS) 
CFLAGS   = -gstabs -O0 -Wall 
NAME     = 2>&1 | c++filt

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

%.o: %.cc $(wildcard ../lib/lib*)
	$(CC) -c $(CFLAGS) $< -o $@ 

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
%.d: %.cc
	$(CC) -M $(CPPFLAGS) $< | sed 's/$*\.o/& $@/g' > $@

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

############################################################################
#
#    .d files
#

sources = $(wildcard *.cc)
dotDs = $(sources:.cc=.d) 
include $(dotDs)


