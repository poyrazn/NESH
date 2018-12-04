#!/bin/bash

#  sort.sh
#  NESH
#
#  Created by Nehir Poyraz on 30.12.2017.
#  Copyright © 2017 Nehir Poyraz. All rights reserved.
if [ $# -eq 2 ]
then
option=$1
lines_ary=(`cat $2`)
else
lines_ary=(`cat $1`)
fi

countreturn=

checkvalid() {
guess=$1
if [[ -n ${guess//[0-9]/} ]]
then
return 1
fi
}

for i in ${lines_ary[@]}
do
checkvalid $i
ret=$?
if [ $ret -eq 1 ]
then
echo "Text file contains non numeric records!"
exit
fi
done

getmax() {
local arr=("${!1}")
max=${arr[0]}
for i in "${arr[@]}"
do
if [ $i -gt $max ]
then
max=$i
fi
done
return $max
}

#takes an array, length and n
countsort(){
local arr=(${!1})
len=$2
arg3=$3
output=()
count=($( for i in {1..10}; do echo 0; done ))

for i in ${arr[@]}
do
(( count[$(( $(( i / arg3 )) % 10 ))]++ ))
done


for (( i = 1; i < 10; i++ ))
do
count[$i]=$(( count[i] + count[$(( i - 1 ))] ))
done


for (( i = len - 1; i >= 0; i-- ))
do
unset output[$(( count[$(( $(( arr[i] / arg3 ))  % 10 ))] - 1 ))]
output[$(( count[$(( $(( arr[i] / arg3 ))  % 10 ))] - 1 ))]=${arr[$i]}
(( count[$(( $(( arr[i] / arg3 )) % 10 ))]-- ))
done

unset arr
arr=${output[@]}
countreturn=${output[@]}
}

#takes an array and len
radixsort(){
local arr=(${!1})
len=$2
getmax arr[@]
max=$?
for(( buck = 1; max / buck > 0; buck *= 10 ))
do
countsort arr[@] $len $buck
unset arr
arr=${countreturn[@]}
done
unset lines_ary
lines_ary=${arr[@]}
}

radixsort lines_ary[@] ${#lines_ary[@]}

ind=0
for i in ${countreturn[@]}; do 
lines_ary[$ind]=$i
(( ind++ ))
done
out=`ls | grep nsort-out.txt`
if [ "$out" = "nsort-out.txt" ]
then
rm $out
else
out="nsort-out.txt"
fi
if [ "$option" == "-d" ]
then
for(( i = ${#lines_ary[@]} - 1; i >= 0; i-- ))
do
echo ${lines_ary[$i]} >> $out
done
else
for i in ${lines_ary[@]}; do echo  $i >> $out ; done
fi

echo "Done!"
