本文内容源于[泰晓科技](http://tinylab.org/elf2bin-part1/)。 原文的例子基于Intel 32位架构，而本文给的例子基于Intel 64位架构。
### 1. 背景简介

有一天，某位同学在讨论群聊起来：

"除了直接把 C 语言程序编译成 ELF 运行以外，是否可以转成二进制，然后通过第三方程序加载到内存后再运行。"

带着这样的问题，我们写了四篇文章，这是其一。

这一篇先介绍如何把 ELF 文件转为二进制文件，然后把二进制文件作为一个 section 加入到另外一个程序，然后在那个程序中访问该 section 并运行。

### 2. 准备工作

先准备一个非常简单的 X64 汇编：hello.s。

这段代码编译、运行后可以打印 Hello World。

### 3. 通过 objcopy 转换为二进制文件

```
as -o hello.o hello.s
ld -o hello hello.o
objcopy -O binary hello hello.bin
```

### 4. 分析转换过后的二进制代码

如果要用 objcopy 做成 Binary 还能运行，怎么办呢？

首先来分析一下，转成 Binary 后的代码如下：

```
acrn@acrn:~/Tools/elf2bin/0001$ hexdump -C hello.bin
00000000  48 c7 c0 01 00 00 00 48  c7 c7 01 00 00 00 48 c7  |H......H......H.|
00000010  c6 a2 00 40 00 48 c7 c2  0d 00 00 00 0f 05 48 c7  |...@.H........H.|
00000020  c0 3c 00 00 00 48 31 ff  0f 05 48 65 6c 6c 6f 2c  |.<...H1...Hello,|
00000030  20 77 6f 72 6c 64 0a                              | world.|
00000037
acrn@acrn:~/Tools/elf2bin/0001$ objdump -d -j .text hello

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



可以发现，Binary只保留了代码部分，其他控制相关的内容全部不见了，非常“纯正”。

需要注意这一行：

```
400086:       48 c7 c6 a2 00 40 00    mov    $0x4000a2,%rsi
```

在 Binary 中，该地址是被写死的。

所以，要让 hello.bin 能够运行，必须要把这段 Binary 装载在指定的位置，即：

```
acrn@acrn:~/Tools/elf2bin/0001$ nm hello | grep " _start"
0000000000400078 T _start
```

这样取到的数据位置才是正确的。

### 5. 如何运行转换过后的二进制

这个是内核压缩支持的惯用做法，先要取到 Load Address，告诉 wrapper kernel，必须把数据解压到 Load Address 开始的位置。

如果这个要在用户空间做呢？

看上去没那么容易，不过可以这么做：

1. 把 hello.bin 作为一个 section 加入到目标执行代码中，比如叫 run-bin.c
2. 然后写 ld script 明确把 hello.bin 放到 Load Address 地址上
3. 同时需要修改 ld script 中 run-bin 本身的加载地址，否则可能会覆盖掉hello.bin中的内容。

### 6. 具体实现

先准备一个 run-bin.c，”bin_entry” 为 hello.bin 的入口，通过 ld script 定义。

接着，拿到 run-bin.o：

```
gcc -c -nostdlib -o run-bin.o run-bin.c
```

把 hello.bin 作为 `.bin` section 加入进 run-bin.o：

```
objcopy --add-section .bin=hello.bin --set-section-flags .bin=contents,alloc,load,readonly run-bin.o
```



ld.script做了两个工作：

1. 把 run-bin 的执行地址往前移动到了 0x300000，避免代码覆盖

2. 获取到 hello 的 _start 入口地址，并把 .bin 链接到这里，可以通过 `nm hello | grep " _start"` 获取;把 bin_entry 指向 .bin section 链接后的入口。


```
acrn@acrn:~/Tools/elf2bin/0001$ gcc -nostdlib -o run-bin run-bin.o -T ld.script
acrn@acrn:~/Tools/elf2bin/0001$ ./run-bin
Hello, world
```



### 7. 小结

在这个基础上，加上压缩/解压支持，就可以类似实现 [UPX](https://upx.github.io/) 了，即类似内核压缩/解压支持。

本文的方法不是很灵活，要求必须把 Binary 装载在指定的位置，否则无法正确获取到数据，后面我们继续讨论如何消除这种限制。

