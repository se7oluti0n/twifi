#!/usr/bin/perl

`sysctl -w dev.wifi0.initslot=0`;
for($i=0; $i <= 15; $i++) {
	`sysctl -w dev.wifi0.dstip=0x889d2689`;
	`sysctl -w dev.wifi0.setslot=$i`;
}
