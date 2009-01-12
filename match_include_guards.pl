#!/usr/bin/perl

# usage: ./include_guard_check.pl */*.h|grep -v Include | sort | include_guard_matcher.pl
#
# This program will match include guards

$target = "none";

while(<>)
{
    if(m/:/)
    {
	$whole_target = $_;
	s/(.*: )(.*)\n?/$2/;
	$target = $_;
#	print "new target found: $target";
    }
    if(m/=/)
    {
	$whole_current = $_;
	s/(.*= )(.*)(  .*\(.*\n?)/$2/;
	$current = $_;
#	print "$target equals $current?\n";
	if($current ne $target)
	{
	    print $whole_target;
	    print $whole_current;
	    print "\n";
	}
    }
}
