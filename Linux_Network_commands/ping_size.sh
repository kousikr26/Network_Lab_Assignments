#!/bin/bash

a=64
while [ $a -lt 2049 ]
do
    
    
    `sudo ping -c 5 udp.jp -s $a -q | grep rtt >> ping_size2.txt`
    a=`expr $a + 20`
done
