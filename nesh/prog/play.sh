#!/bin/sh

#  play.sh
#  NESH
#
#  Created by Nehir Poyraz on 30.12.2017.
#  Copyright © 2017 Nehir Poyraz. All rights reserved.

getdif() {
read dif
case ${dif} in
e) return 10
;;
m) return 100
;;
h) return 0
;;
*)
echo "usage: [e easy] | [m medium] | [h hard]"
return 1
;;
esac
}

checkvalid() {
guess=$1
if [[ -n ${guess//[0-9]/} ]]
then echo "integer expression expected"; return 1
fi
}

echo "Let's play a game."
echo "I'm going to randomly pick a number, and you're going to try to guess it. Don't worry, I'll give you hints along the way!"
echo "Pick your difficulty level:"
echo -e "[e] Easy (1-10)\n[m] Medium (1-100)\n[h] Hard (1-1000)"

getdif
dif=$?
while [ $dif -eq 1 ]
do
getdif
dif=$?
done
if [ $dif -eq 0 ]
then
dif=1000
fi

ran=$(( $RANDOM % $dif + 1 ))
echo "Enter your first guess: "
read guess
checkvalid $guess
ret=$?
while [ $ret -eq 1 ]
do
read guess
checkvalid $guess
ret=$?
done

if [ $guess -eq $ran ]
then
echo "Congratulations! You have guessed it right on the first try!! Way to go."
exit
fi

while [ $guess -ne $ran ]
do
if [ $guess -lt $ran ]
then
echo "You have to guess higher."
else
echo "You have to guess lower."
fi
echo "Enter your next guess: "
read guess
checkvalid $guess
ret=$?
while [ $ret -eq 1 ]
do
read guess
checkvalid $guess
ret=$?
done
done
echo "Congrats! You Won!"
exit
