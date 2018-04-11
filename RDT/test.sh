
#/bin/bash

result=($(free -m))
#$1为重定向的文件
b=$(rm $1)
# https://unix.stackexchange.com/questions/191122/how-to-split-the-string-after-and-before-the-space-in-shell-script
echo  "time:"${result[9]} >> $1
echo  "time:"${result[11]}

