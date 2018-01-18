#/bin/bash
a=0
b=$(rm $1)
while :
do
    a=$(($a+2))
    shared=$(cat /sys/kernel/mm/ksm/pages_shared)
    sharing=$(cat /sys/kernel/mm/ksm/pages_sharing)
    unshared=$(cat /sys/kernel/mm/ksm/pages_unshared)
    memfree=$(cat /proc/meminfo | grep MemFree)
    hugepage=$(cat /proc/meminfo | grep AnonHugePages)

    echo "time:"$a >> $1
    echo "page shared:"$shared >> $1
    echo "page sharing:"$sharing >> $1
    echo "memfree:"$memfree >> $1
    echo "hugepage:"$hugepage >> $1

    echo "time:"$a"s"
    echo "page shared:"$shared 
    echo "page sharing:"$sharing 
    echo "page unshared:"$unshared
    echo "memfree:"$memfree 
    echo "hugepage:"$hugepage
    sleep 2
   
done
