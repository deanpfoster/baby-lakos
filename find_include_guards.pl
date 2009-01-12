#!/usr/bin/perl

# usage: ./include_guard_check.pl */*.h | sort
#
# It will find include guards in both the orginal header file and the new file

$/ = "\n\n";
while(<>)
{
    next if ! m/\#ifndef/;
    s!//.*\n!!g;
    if(m/\include/)
    {
	next if(m/\#define/);
	s/(\#ifndef )([^\n]*)(\n\#include ")([^\n]*)("(.*\n)*.*)/$4 = $2 /ig;
	s/$/ (in $ARGV)\n/;
	print;
    }
    if(m/\#define/)
    {
	s/(\n?\#ifndef )([^\n]*)(\n\#define )([^\n]*)((.*\n)*.*)/$2/ig;
	s/^/$ARGV : /;
	s/$/\n/;
	print;
	s!.*/!!;
	print;
    }

}
