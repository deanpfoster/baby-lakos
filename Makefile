#  $Id: Makefile 2013 2000-09-01 21:13:45Z foster $
#
#  $Source$
#


###########################################################################
#
#			TARGETS
#

all:

clean:
	-rm -f */*.o  
	-rm -f */*.d
	-rm -f */*~ 
	-rm -f */a.out 
	-rm -f */core  
	-rm -f lib/lib*.a 
	-rm -f */*.executable 
	-rm -f */*.OK 
	-rm -f */test 
	-rm -f */*.results
	-rm -f */local_library.a
	-rm -rf Include/*

install: directories  
	-rm `ls -lF */*.d | grep " 0 " | sed "s/.* //g" | tr "\n" " "`
	-cd one;       make install
	-cd two;       make install

install2: directories  
	-rm `ls -lF */*.d | grep " 0 " | sed "s/.* //g" | tr "\n" " "`
	make -C one   install
	make -C two   install

evil: directories  
	-touch Include/tmp.d;rm `ls -lF */*.d | grep " 0 " | sed "s/.* //g" | tr "\n" " "`
	-cd one;       if ! make -q local ; then make local;touch test;make install;rm test;fi
	-cd two;       if ! make -q local ; then make local;touch test;make install;rm test;fi

pure: directories  
	-touch Include/tmp.d;rm `ls -lF */*.d | grep " 0 " | sed "s/.* //g" | tr "\n" " "`
	-cd one;         if ! make -q test ; then make test;fi
	-cd two;         if ! make -q test ; then make test;fi

############################################################################
#
#                      LEVELIZATION
#
#
#   level 0:  one
#   level 1:  two
#   level 2:  
#
# top level: mains
#
#

lib/libtwo.a: lib/libone.a 

mains: lib/libtwo.a 

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #

all:directories mains

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #

directories: Include one/one  two/two

Include:
	-mkdir -p Include

one/one:
	ln -s . one/one

two/two:
	ln -s . two/two

lib/lib%.a: 
	-cd $*; $(MAKE) install
