#/bin/bash

cmd="numactl -H | grep 'node 1 free'"

while true
do 
eval "$cmd"

sleep 1
done
