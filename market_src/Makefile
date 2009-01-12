#  $Id: Makefile 244 2000-03-10 22:33:15Z foster $
#
#  $Source$
#

#LDFLAGS = -L../lib
OPT = -O0

# Examples of depending on libaries
#
#  LDLIBS = -lgo_basics -lcontext 
#  libs_used = ../lib/libgo_basics.a ../lib/libcontext.a

#INCLUDES = -I../Include 

###########################################################################
#
# Definitions  (gnu-make wants them first)
#

testing_sources=$(testing_sources_in_directory) $(testing_sources_from_RCS)

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #
# Or you can list them out one at a time:				  #
#									  #
#   testing_sources = foo.test.cc bar.test.cc  ....			  #
#									  #
# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #


###########################################################################
#
#			TARGETS
#

testing: test

sub_dir = none


clean: 
	-../rmo
	-../cleanup

main: main.o test
	g++ main.o simulation.o market.o order_generator.o order.o market_units_transformations.o unit.o basic_unit.o market_units.o system.o -o main

gp:
	mkfifo gp

gv:
	mkfifo gv

screens: main gp gv
	gnuplot gp - &
	gnuplot gv - &

screen: main gp gv
	gnuplot gp - &
	gnuplot gv - &

############################################################################
#
#                      LEVELIZATION
#

level_0 = system.o
level_1 = basic_unit.o market_units.o
level_2 = unit.o
level_3 = market_units_transformations.o
level_4 = order.o
level_5 = market.o order_generator.o
level_6 = simulation.o
level_7 = 
level_8 =
level_9 =

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #
 
above_1 = $(level_0) 
above_2 = $(level_1) $(above_1)
above_3 = $(level_2) $(above_2)
above_4 = $(level_3) $(above_3)
above_5 = $(level_4) $(above_4)
above_6 = $(level_5) $(above_5)
above_7 = $(level_6) $(above_6)
above_8 = $(level_7) $(above_7)
above_9 = $(level_8) $(above_8)

above_infinity = $(above_9)

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #
# Creating the dependencies for testing executables.  Using the
# following automatic setup will mean that all levels must be
# made even if they aren't really depended on.

$(level_0:.o=.test.executable):            $(libs_used)
$(level_1:.o=.test.executable): $(above_1) $(libs_used) 
$(level_2:.o=.test.executable): $(above_2) $(libs_used)
$(level_3:.o=.test.executable): $(above_3) $(libs_used)
$(level_4:.o=.test.executable): $(above_4) $(libs_used) 
$(level_5:.o=.test.executable): $(above_5) $(libs_used) 
$(level_6:.o=.test.executable): $(above_6) $(libs_used)
$(level_7:.o=.test.executable): $(above_7) $(libs_used)
$(level_8:.o=.test.executable): $(above_8) $(libs_used)
$(level_9:.o=.test.executable): $(above_9) $(libs_used)

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #
#									  #
# Alternatively you can list them explicitely to save link time           #
# I.e.									  #
#	foo.test.executable: bar.o					  #
#									  #
# Should you write non-levelized code, you will have to list 		  #
# dependences explicitely.						  #
#									  #
# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #


############################################################################
#
#            INCLUDING OUR RULES AND DEFINITIONS
#
#

include rules_for_makefiles

