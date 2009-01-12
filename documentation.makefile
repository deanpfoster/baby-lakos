$Id: documentation.makefile 2025 2000-09-09 15:38:10Z foster $   -*-text-*-

PROJECT PURPOSE AND SUMMARY
===========================

This is a collection of files to implement a simple version of John
Lakos' amazing book _Large-scale C++ Software Design_.  The goal is to
decrease the overhead of implementing levelization.  The goal is to
have a Makefile that is very easy to read and keep current.

It enforces regression testing.  It strongly encourages levelization.
It provides simple templates to help remind authors of style
guidelines.  It works well with CVS.

LIMITATIONS
===========

It requires gnu-make, has gcc hard wired in, and generally is set up
for running under linux.  


GENERAL SUMMARY
===============

The primary assumption is that you will ALWAYS write a testing program
for each and every class.  Since this is such a pain, the system tries
to make that as easy as possible.

	To use this system, first edit the ./generic.* files to match
whatever style of naming conventions you like best.  Then to create a
new class, copy these generic.* files to the library to create the
following three files:

		   foo.h = declaration
	          foo.cc = definitions
	     foo.test.cc = examples of how to use Foo and testing of Foo

Now edit them to implement the class Foo.  Finally add "foo.o"
somewhere in the Makefile levelization section.  Now do a "make
foo.OK" and the following will be generated:

    	          foo.d  = the dependencies of foo.cc
             foo.test.d  = the dependencies for foo.test.cc
	           foo.o = object 
  	      foo.test.o = object (temp)
     foo.test.executable = testing executable (temp)
        foo.test.results = output of the sample code (temp)

At this point the system will have compiled the class, and ran the
foo.test.cc file to generate the output.  It will then try to compare
this output to the regression output.  (Which currently doesn't
exist).  So you should look at the output and certify that it did the
right thing.  Then copy it to foo.test.results_correct.  Now when you
rerun the "make foo.OK" you will have the following two files added: 

foo.test.results_correct = output of the sample code (temp)

 	          foo.OK = signifies passing regression testing

Finally if you run a plan "make" or a "make test" or a "make install"
the system will generate *.OK's and then generate a file called:

                    test = signifies passing ALL regression tests	


LEVELIZATION
============

If a class Bar depends on another class, then we have to put it at
level_2 of the Makefile.  This requires putting Foo as a "level 1"
item and the class it depends on as a "level 0" item.  (For example,
the sample Makefile has bar depending on foo).

LIBRARY LEVEL MAKES
===================

make foo.OK  : Tries to compile, link, run and regression test foo.cc. 

make test    : tries to generate *.OK

make         : runs "make test"

make install : copies *.h to ../Include/*.  Builds a library and copies
               it to ../lib/*


TOP LEVEL MAKES
===============

make          : update any libraries that are out of date relative to
                libraries that have been installed already.

make install  : runs a make install on each library.

make evil     : tricks the system into generating libraries and copying
		the .h files WITHOUT running any regression testing.
		This saves link time and run time.  So it is very
		fast, but it undermines the entire reason for building
		this whole system! 


make pure     : Runs a make test in each library.


UTILITIES
=========

The only utility provided at the moment is a include guard checker.
Run "include_guarding" from the top level.  It will check all your
*/*.h files to see if some of them use an incorrect name for an
include guard of some other file.  For example, two/foo.h has an error
that is caught by this program.


WHY RUN MAKE EVIL?
==================

The reason I find myself using "make evil" is when I detect a error
in a low level library while running some high level code.  Of course
this means that the *.test.cc files are not doing their job.  So what
I will sometimes do is to try to find the error by using the high
level system for testing.  This requires rebuilding all intervening
libraries AND generating 100's of executables and running all of
them.  I can't wait that long (since I never took up coffee).  So I
run make evil.  This is the call of the dark side!

So you think regression testing is really cool--but your on a slow
machine.  So it takes FOREVER to to the linking.  Your sure you
haven't actually introduced any errors.  You want to see how the new
library effects some other code.  You are looking for a "fast make"
that doesn't actually do all these regression tests.  Take the
following oath: "I PROMISE to ALWAYS do regression tests as soon as I
buy a new CPU."  Now you may run "make evil".  This can be up to 10
times faster. 

After you have been taken over by the dark-side, read a chapter of
Lakos so the force will be with you!

CVS
===

Add the following to your cvsignore:

*.d
*.executable
*.results
*.OK
Include
test

(Detailed instructions: cvs co CVSROOT; cd CVSROOT; edit cvsignore;
cvs ci; cd ..;rm -rf CVSROOT)


BUGS
====

(1) If you delete a .h file in a directory, it doesn't get deleted in
    the ../Include/*/* directory.  So other libraries can still use the
    obsolete .h file, but obviously the .cc file no longer exists.  

