
To disable THP at run time

`echo  never > /sys/kernel/mm/transparent_hugepage/enabled`


To enable THP at run time

`echo  always > /sys/kernel/mm/transparent_hugepage/enabled`

Check system-wide THP usage

`grep AnonHugePages /proc/meminfo `
  



---
参考资料：
1. [redhat](https://access.redhat.com/solutions/46111)
1. [透明大页介绍](http://www.cnblogs.com/kerrycode/p/4670931.html)
