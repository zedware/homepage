#!/bin/sh

#set -x

usage()
{
    echo "Usage: `basename $0` [-all]"
    echo "  Without -all: Remove IPCs owned by current user."
    echo "  With -all: Remove all IPCs (root)."
    exit 1
}

if [ $# -gt 1 ]
then
    usage
fi

all="no"
if [ $1='-all' ]
then
    all="yes"
fi

s=$HOME/s.$$
m=$HOME/m.$$
q=$HOME/q.$$

user=`whoami`

if [ ! "all"="yes" ]
then
    ipcs -s | grep "^0x" | awk '$3==ENVIRON["user"] {print $2}' > $s
    ipcs -m | grep "^0x" | awk '$3==ENVIRON["user"] {print $2}' > $m
    ipcs -q | grep "^0x" | awk '$3==ENVIRON["user"] {print $2}' > $q
else
    ipcs -s | grep "^0x" | awk '{print $2}' > $s
    ipcs -m | grep "^0x" | awk '{print $2}' > $m
    ipcs -q | grep "^0x" | awk '{print $2}' > $q
fi

for loop in `cat $s`
do
    echo "ipcrm -s $loop"
    ipcrm -s $loop                                     
done

for loop in `cat $m`
do
    echo "ipcrm -m $loop"
    ipcrm -m $loop
done

for loop in `cat $q`
do
    echo "ipcrm -q $loop"
    ipcrm -q $loop
done

rm -rf $s $q $m   