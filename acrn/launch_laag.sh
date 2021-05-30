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

function tap_net() {
# create a unique tap device for each VM
tap=$1
tap_exist=$(ip a | grep "$tap" | awk '{print $1}')
if [ "$tap_exist"x != "x" ]; then
  echo "tap device existed, reuse $tap"
 else
  ip tuntap add dev $tap mode tap
fi

# if acrn-br0 exists, add VM's unique tap device under it
br_exist=$(ip a | grep acrn-br0 | awk '{print $1}')
if [ "$br_exist"x != "x" -a "$tap_exist"x = "x" ]; then
  echo "acrn-br0 bridge aleady exists, adding new tap device to it..."
  ip link set "$tap" master acrn-br0
  ip link set dev "$tap" down
  ip link set dev "$tap" up
fi
}

function launch_windows()
{

#vm-name used to generate uos-mac address
mac=$(cat /sys/class/net/e*/address)
vm_name=post_vm_id$1
mac_seed=${mac:0:17}-${vm_name}

tap_net tap0

#check if the vm is running or not
vm_ps=$(pgrep -a -f acrn-dm)
result=$(echo $vm_ps | grep -w "${vm_name}")
if [[ "$result" != "" ]]; then
  echo "$vm_name is running, can't create twice!"
  exit
fi

echo ${passthru_vpid["gpu"]} > /sys/bus/pci/drivers/pci-stub/new_id
echo ${passthru_bdf["gpu"]} > /sys/bus/pci/devices/${passthru_bdf["gpu"]}/driver/unbind
echo ${passthru_bdf["gpu"]} > /sys/bus/pci/drivers/pci-stub/bind
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
   -s 2,passthru,0/2/0,gpu  \
   --ovmf ./OVMF.fd \
   -s 1:0,lpc \
   $vm_name
}
launch_windows 1
