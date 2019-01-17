 if COMPACTION is enabled
 
`sudo cat /sys/kernel/debug/extfrag/unusable_index`

else

参考[Pintu Kumar](http://events17.linuxfoundation.org/sites/events/files/slides/%5BELC-2015%5D-System-wide-Memory-Defragmenter.pdf)p5-p6

```python
# -*- coding: UTF-8 -*-
import os
import math
import time

# reference:http://events17.linuxfoundation.org/sites/events/files/slides/%5BELC-2015%5D-System-wide-Memory-Defragmenter.pdf p4-p6

while True:
    result = os.popen("cat /proc/buddyinfo | grep 'Node 1'").read().split()
    total_free_pages = 0
    for i in range(4, 15):
        total_free_pages = total_free_pages + int(result[i]) * pow(2, i-4)
    tem = pow(2, 9) * int(result[13]) + pow(2, 10) * int(result[14])
    frag_level = (total_free_pages - tem) * 100 / total_free_pages
    print(frag_level)

    time.sleep(2)
```


---
参考资料：
1. [Pintu Kumar](http://events17.linuxfoundation.org/sites/events/files/slides/%5BELC-2015%5D-System-wide-Memory-Defragmenter.pdf)p5-p7
1. [Linux 内存碎片化检视之 buddy_info | extfrag_index | unusable_index](https://blog.csdn.net/memory01/article/details/80958009)
1. [Techniques to overcome higher order allocation failure due to fragmentation](https://elinux.org/images/a/a8/Controlling_Linux_Memory_Fragmentation_and_Higher_Order_Allocation_Failure-_Analysis%2C_Observations_and_Results.pdf)
