#/bin/bash
mbl=$1

last_mbm_local=$(cat $mbl)
while :
do	sleep 1
	cur_mbm_local=$(cat $mbl)
	mbm_local_1s=$((cur_mbm_local-$last_mbm_local))
	echo $mbm_local_1s
	echo $mbm_local_1s >> $2
	last_mbm_local=$cur_mbm_local
done

