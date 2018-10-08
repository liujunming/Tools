
To disable THP at run time

`echo  never > /sys/kernel/mm/transparent_hugepage/enabled`


To enable THP at run time

`echo  always > /sys/kernel/mm/transparent_hugepage/enabled`

How to tell if Explicit HugePages is enabled or disabled

 `grep -i HugePages_Total /proc/meminfo`
- Explicit HugePages DISABLED:
  - If the value of HugePages_Total is "0" it means HugePages is disabled on the system.
- Explicit HugePages ENABLED:
  - If the value of HugePages_Total is greater than "0", it means HugePages is enabled on the system.
  



---
参考资料：
1. [redhat](https://access.redhat.com/solutions/46111)
1. [透明大页介绍](http://www.cnblogs.com/kerrycode/p/4670931.html)
