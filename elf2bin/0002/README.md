本文内容源于[泰晓科技](http://tinylab.org/elf2bin-part2/)。 原文的例子基于Intel 32位架构，而本文给的例子基于Intel 64位架构。

### 1. 背景简介

[上篇](https://github.com/liujunming/Tools/tree/master/elf2bin/0001) 介绍了如何把 ELF 文件转成二进制文件，并作为一个新的 Section 加入到另外一个程序中执行。

用了一个定制化的 ld script，把 Binary Seciton 的加载地址（运行时地址）写死。



### 2. RIP relative addressing解决绝对地址问题

本篇来讨论一个有意思的话题，那就是，是否可以把这个绝对地址给去掉，只要把这个 Binary 插入到新程序的 Text 中，不关心加载地址，也能运行？

 很幸运，[How to use x64 RIP-relative addressing](http://liujunming.top/2021/04/11/How-to-use-x64-RIP-addressing/)帮我们解决了绝对地址问题。

### 3. 链接脚本简化

生成的 hello.bin 链接到 run-bin，就不需要写死加载地址了，随便放，而且不需要调整 run-bin 本身的加载地址，所以 ld.script 的改动可以非常简单。

```
acrn@acrn:~/Tools/elf2bin/0002$ as -o hello.o hello.s
acrn@acrn:~/Tools/elf2bin/0002$ ld -o hello hello.o
acrn@acrn:~/Tools/elf2bin/0002$ objcopy -O binary hello hello.bin
acrn@acrn:~/Tools/elf2bin/0002$ gcc -c -nostdlib -o run-bin.o run-bin.c
acrn@acrn:~/Tools/elf2bin/0002$ objcopy --add-section .bin=hello.bin --set-section-flags .bin=contents,alloc,load,readonly run-bin.o
acrn@acrn:~/Tools/elf2bin/0002$ gcc -nostdlib -o run-bin run-bin.o -T ld.script
acrn@acrn:~/Tools/elf2bin/0002$ ./run-bin
Hello, world
```

### 4. 直接用内联汇编嵌入二进制文件

其实可以做一个简化，直接用 `.pushsection` 和 `.incbin` assembler directives把 `hello.bin` 插入到 run-bin 即可，无需额外的链接脚本。

```
acrn@acrn:~/Tools/elf2bin/0002$ as -o hello.o hello.s
acrn@acrn:~/Tools/elf2bin/0002$ ld -o hello hello.o
acrn@acrn:~/Tools/elf2bin/0002$ objcopy -O binary hello hello.bin
acrn@acrn:~/Tools/elf2bin/0002$ gcc -c -nostdlib -o run-bin.o run-bin2.c
acrn@acrn:~/Tools/elf2bin/0002$ gcc -o run-bin run-bin.o
acrn@acrn:~/Tools/elf2bin/0002$ ./run-bin
Hello, world
```



### 5小结

本文通过RIP-relative addressing ，不再需要把 Binary 文件装载到固定的位置。

另外，也讨论到了如何用 `.pushsection/.popsection` 替代 ld script 来添加新的 Section。