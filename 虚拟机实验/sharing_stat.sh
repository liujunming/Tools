#/bin/bash
a=0
b=$(rm $1)
sleep 50
while :
do
    a=$(($a+2))
    sharing=$(cat /sys/kernel/mm/ksm/pages_sharing)
 
    echo "time: "$a >> $1
    echo "page sharing: "$sharing >> $1


    echo "time: "$a"s"
    echo "page sharing: "$sharing 

    sleep 2
   
done
