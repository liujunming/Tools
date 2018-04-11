
#/bin/bash

result=($($1))

b=$(rm $2)

echo  "time:"${result[9]} >> $2
echo  "time:"${result[11]}
