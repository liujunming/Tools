ssh test@210.45.114.192 -p 55566

---

- virsh start ljm1    
  - ssh test@192.168.122.140 

- virsh start ljm2    
  - ssh test@192.168.122.236

- virsh start ljm3    
  - ssh test@192.168.122.219

- virsh start ljm4    
  - ssh test@192.168.122.71

- virsh start ljm5    
  - ssh test@192.168.122.59

- virsh start ljm6    
  - ssh test@192.168.122.17

- virsh start ljm7    
  - ssh test@192.168.122.227

- virsh start ljm8    
  - ssh test@192.168.122.63

---
benchmark：
- graph500

  ./graph500.sh

  /home/test/graph500-master/seq-csr/seq-csr -s 22 -e 16
---
- liblinear

  cd /home/test/liblinear-2.20 && time ./train -s 7 url_combined
 
 ---------------------------------------------------------------------------------------------------------------------------------------
-  MicroIO

   vmtouch -t sample.txt
  
----------------------------------------------------------------------------------------------------------------------------------------
- 内核编译

  cd /home/test/linux-4.9.58 && make
---
- sysbench-cpu

  sysbench --test=cpu --cpu-max-prime=50000 run
---
- filebench

  su

  cd /usr/local/share/filebench/workloads && filebench -f filemicro_rread.f


---
- SPECjbb

  cd SPECjbb2005-master/ && ./run.sh
  

---

python3 fra_stat.py

./test.sh 1.txt

python3 fmfi.py

python3 buddy.py

./free.sh

./numa.sh

./stat.sh 1.txt

gcc frag.c -o a

perl -e 'print "a" x 2684354560' > test.txt




./test.sh 1.txt

python3 ./test.py

scp -P 55566 -i ~/.ssh/401server test@210.45.114.192:/var/log/syslog /home/ljm/
