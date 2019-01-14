virsh start ljm7    ssh test@192.168.122.53


安装： `sudo apt-get install redis-server`
  
  
运行：`redis-cli`


To remove all the keys of all the existing database, run: `redis-cli FLUSHALL`


禁止持久化： /etc/redis/redis.conf https://zhuanlan.zhihu.com/p/20599481



---
参考资料：

1. http://blog.fens.me/linux-redis-install/
