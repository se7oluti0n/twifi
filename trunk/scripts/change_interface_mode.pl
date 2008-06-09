#!/usr/bin/perl

$mode = ap;
$if="ath0";
$index=0;

if($#ARGV>=0){
	$if=$ARGV[0];
}
if($#ARGV>=1){
	$index=$ARGV[1];
}
if($#ARGV>=2){
	$mode=$ARGV[2];
}

print "set $if to mode $mode on wifi$index\n";

`ifconfig $if down`;
`wlanconfig $if destroy`;
`wlanconfig $if create wlandev wifi$index wlanmode $mode`;
