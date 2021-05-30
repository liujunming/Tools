#!/bin/bash
# board: TGL-RVP, scenario: INDUSTRY, uos: WINDOWS
# pci devices for passthru
declare -A passthru_vpid
declare -A passthru_bdf

passthru_vpid=(
["gpu"]="8086 5a85"
)
passthru_bdf=(
["gpu"]="0000:00:02.0"
)

function launch_windows()
{

#vm-name used to generate uos-mac address
mac=$(cat /sys/class/net/e*/address)
vm_name=post_vm_id$1
mac_seed=${mac:0:17}-${vm_name}


#setup bridge for uos network
br=$(brctl show | grep acrn-br0)
br=${br-:0:6}
ip tuntap add dev tap0 mode tap

# if bridge not existed
if [ "$br"x != "acrn-br0"x ]; then
	#setup bridge for uos network
	brctl addbr acrn-br0
	brctl addif acrn-br0 enp3s0
	ifconfig enp3s0 0
	dhclient acrn-br0
fi

# Add TAP device to the bridge
brctl addif acrn-br0 tap0
ip link set dev tap0 up

#check if the vm is running or not
vm_ps=$(pgrep -a -f acrn-dm)
result=$(echo $vm_ps | grep -w "${vm_name}")
if [[ "$result" != "" ]]; then
  echo "$vm_name is running, can't create twice!"
  exit
fi

mem_size=2048M
#interrupt storm monitor for pass-through devices, params order:
#threshold/s,probe-period(s),intr-inject-delay-time(ms),delay-duration(ms)
intr_storm_monitor="--intr_monitor 10000,10,1,100"

#logger_setting, format: logger_name,level; like following
logger_setting="--logger_setting console,level=4;kmsg,level=3;disk,level=5"

./acrn-dm -A -m $mem_size -s 0:0,hostbridge -U d2795438-25d6-11e8-864e-cb7a18b34643 \
   $logger_setting \
   -s 7,virtio-console,@stdio:stdio_port \
   -s 4,virtio-blk,./laag.img \
   -s 5,virtio-net,tap0 \
   --ovmf ./OVMF.fd \
   -s 1:0,lpc \
   $vm_name
}
launch_windows 1
