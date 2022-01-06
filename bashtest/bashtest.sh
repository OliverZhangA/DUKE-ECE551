#!/bin/bash

variable="hello world"
echo $variable

for i in onefish twofish redfish
do
    echo "current fish is $i"
done

for i in 'find  . -name \*.c'
do
    echo " "
done

#replace - in filename with _
for i in *_*
do
    mv $i `echo $i | tr _ -`
done

echo $PATH
