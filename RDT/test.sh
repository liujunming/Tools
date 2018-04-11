
#/bin/bash

# $1为command，如free $2为输出文件名
result=($($1))
b=$(rm $2)
# https://unix.stackexchange.com/questions/191122/how-to-split-the-string-after-and-before-the-space-in-shell-script
echo  "time:"${result[9]} >> $2
echo  "time:"${result[11]}

