#!/bin/sh

#  convert.sh
#  NESH
#
#  Created by Nehir Poyraz on 30.12.2017.
#  Copyright © 2017 Nehir Poyraz. All rights reserved.
FROM=
TO=
CONB=

getopt() {
arg=$1
if [ $arg -eq 1 ]
then
read option
case ${option} in
b) FROM="binary"
return 2 ;;
o) FROM="octal"
return 8 ;;
d) FROM="decimal"
return 10 ;;
h) FROM="hexadecimal"
return 16 ;;
*) echo "usage: [b] binary | [o] octal | [d] decimal | [h] hexadecimal"
return 1 ;;
esac
else
read option
case ${option} in
b) TO="binary"
return 2 ;;
o) TO="octal"
return 8 ;;
d) TO="decimal"
return 10 ;;
h) TO="hexadecimal"
return 16 ;;
*) echo "usage: [b] binary | [o] octal | [d] decimal | [h] hexadecimal"
return 1 ;;
esac
fi

}

checkvalid() {
number=$1
regex="+\(\[0-9a-f\]\)"
if ! [[ "$number" =~ "+\(\[0-9a-f\]\)" ]]
then echo "$number is not valid. Enter another number. "; return 1
fi
}

convert_binary() {
arg=$1
while [ $arg -ne 0 ]
do
IntrmValue=$(expr $arg % 2)
CONB=$IntrmValue$CONB
arg=$(expr $arg / 2)
done
}

echo "Convert from:"
echo -e "[b] binary\n[o] octal\n[d] decimal\n[h] hexadecimal"
getopt 1
from=$?
while [ $from -eq 1 ]
do
getopt 1
from=$?
done
echo "Convert from $FROM to:"
echo -e "[b] binary\n[o] octal\n[d] decimal\n[h] hexadecimal"
getopt 2
to=$?
while [ $to -eq 1 ]
do
getopt 2
to=$?
done
echo "Enter a number to be converted from $FROM to $TO"
read Number
cond=$(($from#$Number))
case ${to} in
2) convert_binary $cond
cond=$CONB
printf 'The result is: %d\n' $cond ;;
8) printf 'The result is: %o\n' $cond ;;
10) printf 'The result is: %d\n' $cond ;;
16) printf 'The result is: %x\n' $cond ;;
esac


