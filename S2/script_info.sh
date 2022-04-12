#!/bin/sh
#ps -e | grep 26503 objectiu field propietari i nom

a=`ps -e -f | awk '{print $1" "$2" "$8}' | grep $1`
usr=`echo $a | cut -d ' ' -f 1`
cmd=`echo $a | cut -d ' ' -f 3`
echo UID del programa $usr creat per la comanda $cmd 
