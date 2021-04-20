本文内容源于[泰晓科技](http://tinylab.org/elf2bin-part4/)。 原文的例子基于Intel 32位架构，而本文给的例子基于Intel 64位架构。

# 动态计算并修改数据加载地址

### 1. 背景简介

前面几篇把汇编、静态链接、静态加载、动态加载都讲了，还差一个缺憾，那就是动态链接。

每次得加载到一个特定地址其实不是那么灵活，所以，在不修改代码的前提下，如果能保证加载到任意地址，而且还能访问数据的话，就需要“动态链接”。

### 2. 动态计算数据地址

就是数据的地址可以动态分配，本文模拟一下这个过程。


```
as -o hello.o hello.s
ld -o hello hello.o
objcopy -O binary hello hello.bin
```

```
acrn@acrn:~/Tools/elf2bin/0004$ objdump -d hello.o

hello.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_start>:
   0:   48 c7 c0 01 00 00 00    mov    $0x1,%rax
   7:   48 c7 c7 01 00 00 00    mov    $0x1,%rdi
   e:   48 c7 c6 00 00 00 00    mov    $0x0,%rsi
  15:   48 c7 c2 0d 00 00 00    mov    $0xd,%rdx
  1c:   0f 05                   syscall
  1e:   48 c7 c0 3c 00 00 00    mov    $0x3c,%rax
  25:   48 31 ff                xor    %rdi,%rdi
  28:   0f 05                   syscall

000000000000002a <message>:
  2a:   48                      rex.W
  2b:   65 6c                   gs insb (%dx),%es:(%rdi)
  2d:   6c                      insb   (%dx),%es:(%rdi)
  2e:   6f                      outsl  %ds:(%rsi),(%dx)
  2f:   2c 20                   sub    $0x20,%al
  31:   77 6f                   ja     a2 <message+0x78>
  33:   72 6c                   jb     a1 <message+0x77>
  35:   64                      fs
  36:   0a                      .byte 0xa
acrn@acrn:~/Tools/elf2bin/0004$ objdump -d hello

hello:     file format elf64-x86-64


Disassembly of section .text:

0000000000400078 <_start>:
  400078:       48 c7 c0 01 00 00 00    mov    $0x1,%rax
  40007f:       48 c7 c7 01 00 00 00    mov    $0x1,%rdi
  400086:       48 c7 c6 a2 00 40 00    mov    $0x4000a2,%rsi
  40008d:       48 c7 c2 0d 00 00 00    mov    $0xd,%rdx
  400094:       0f 05                   syscall
  400096:       48 c7 c0 3c 00 00 00    mov    $0x3c,%rax
  40009d:       48 31 ff                xor    %rdi,%rdi
  4000a0:       0f 05                   syscall

00000000004000a2 <message>:
  4000a2:       48                      rex.W
  4000a3:       65 6c                   gs insb (%dx),%es:(%rdi)
  4000a5:       6c                      insb   (%dx),%es:(%rdi)
  4000a6:       6f                      outsl  %ds:(%rsi),(%dx)
  4000a7:       2c 20                   sub    $0x20,%al
  4000a9:       77 6f                   ja     40011a <message+0x78>
  4000ab:       72 6c                   jb     400119 <message+0x77>
  4000ad:       64                      fs
  4000ae:       0a                      .byte 0xa
```

我们希望在运行时根据 Binary 文件加载的位置，动态计算出数据地址。

```
 400078:       48 c7 c0 01 00 00 00    mov    $0x1,%rax
 40007f:       48 c7 c7 01 00 00 00    mov    $0x1,%rdi
 400086:       48 c7 c6 a2 00 40 00    mov    $0x4000a2,%rsi
```

`$0x4000a2`是hardcode的值，同时，该值相对于.text section开始位置的offset为17。(7+7+3=17)

从`objdump -d hello.o`的结果`000000000000002a <message>:`可知，message相对于.text section开始位置的offset为0x2a。



### 3. 动态修改数据地址

上面得到了两个关键信息：

1. 数据偏移（相对 .text 起始位置）：0x2a
2. 代码偏移（相对 .text 起始位置）：17，这个地方要写入上面的地址

需要做的是，用 .text addr + 0x2a 算出数据地址，然后写入 .text addr + 17 这个位置。

说明一下，在实际的动态链接中，上面两个地址都是可以根据 ELF 中的相关数据，动态计算出来的，这里因为是用到了 Binary 文件，我们通过 `objdump/readelf` 获取到数据访问指令地址和数据偏移后来模拟动态计算。



.text addr 这个地址在运行时确定，这里由 `mmap` 动态获得， 这部分代码在mmap.absolute.c中，核心部分如下：

```c
addr = (char *)0x04200000;
addr = mmap(addr, length, PROT_READ | PROT_WRITE | PROT_EXEC,
            MAP_PRIVATE | MAP_FIXED, fd, offset);

/* update the data address */
#define inst_offset 17
// data_offset = 0x04200000 + 0x2a
*(addr + inst_offset) = 0x2a;
*(addr + inst_offset + 1) = 0x00;
*(addr + inst_offset + 2) = 0x20;
*(addr + inst_offset + 3) = 0x04;
```

addr 即 `mmap` 加载 Binary 文件到内存时分配的地址，也是 .text 的起始地址。

编译和运行如下：


```
acrn@acrn:~/Tools/elf2bin/0004$ gcc -o mmap_absolute mmap.absolute.c
acrn@acrn:~/Tools/elf2bin/0004$ ./mmap_absolute
Hello, world
```

如上演示，这里不再需要提前把 hello 链接到一个“合法”的地址，而是让 `mmap` 自己合理分配一个，当然，也兼容自己指定一个合法的加载地址。

mmap.absolute.c还用了`__builtin___clear_cache`，这个函数是 gcc 提供的，详细介绍在 [c - Is there a way to flush the entire CPU cache…](https://stackoverflow.com/questions/48527189/is-there-a-way-to-flush-the-entire-cpu-cache-related-to-a-program)。

> note that `__builtin__clear_cache` compiles to zero instructions for x86, but has an effect on surrounding code: without it, gcc can optimize away stores to a buffer before casting to a function pointer and calling. (It doesn't realize that data is being used as code, so it thinks they're dead stores and eliminates them.)

### 4. 小结

未来可以考虑进一步完善 Binary 文件结构，以实现动态链接的功能。

到这里，四篇文章，比较系统地介绍了如何把一个 ELF 文件转换为 Binary 文件，并通过第三方程序加载和执行，内容涉及静态嵌入、位置无关、动态加载以及动态计算和修改数据地址。