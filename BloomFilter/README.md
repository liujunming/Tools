假设我们有16M个元素，若`#define N 1024*1024*64`，则定义了64M个bits,所以bits-per-key = 4。

```c	
set_bitmap(checksum & 0x03FFFFFF, bitmap);
set_bitmap(checksum>>3 & 0x03FFFFFF, bitmap);
set_bitmap(checksum>>6 & 0x03FFFFFF, bitmap);
```
上述代码相当于定义了3个hash函数。
