#!/bin/bash
#以小时循环
#sh x.sh 2017010101 2017010301

stime=$1
etime=$2
while :
do
    echo $stime
    stime=$(date -d "${stime:0:8} ${stime:8:2} 1hour"  +%Y%m%d%H)
    if [[ $stime -gt $etime ]]
    then
        break   
    fi  
done