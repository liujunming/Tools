本文内容源于[泰晓科技](http://tinylab.org/elf2bin-part3/)。 原文的例子基于Intel 32位架构，而本文给的例子基于Intel 64位架构。

### 1. 背景简介

前面两篇分别讨论了如何把一个转成 Binary 的 ELF 作为一个新的 Section 加入到另外一个程序中执行：

- [ELF转二进制: 用 objcopy 把 ELF 转成 Binary 并运行](https://github.com/liujunming/Tools/tree/master/elf2bin/0001)
- [ELF转二进制：允许把 Binary 文件加载到任意位置](https://github.com/liujunming/Tools/tree/master/elf2bin/0002)

### 2. 如何实现动态加载和运行

本文继续讨论，但是方向是，在运行时加载 Binary 并运行，支持前面两篇中的两种类型的 Binary：绝对数据地址、相对数据地址。

#### 2.1 先加载RIP相对地址的 Binary 文件

先来考虑最简单的相对数据地址，动态加载后，仅需考虑把加载的 Binary 所在内存范围设置可执行即可。

把文件加载到内存中并设置内存保护属性的最佳方式是` mmap`，当然也可以用 `malloc`/`memalgin` 分配内存然后用 `mprotect` 设置内存保护属性，但是需要额外考虑对齐。



mmap.relative.c主要完成两个功能:

1. 调整内存保护属性为 `MAP_EXEC`
2. 把映射完的随机地址转换为一个 `void (*)void` 函数，然后直接执行，也就是调用 Binary

```
acrn@acrn:~/Tools/elf2bin/0003$ gcc -o mmap_relative mmap.relative.c
acrn@acrn:~/Tools/elf2bin/0003$ ./mmap_relative
Hello, world
```

#### 2.2 再讨论数据绝对地址的 Binary 文件

如果要带绝对地址的 hello.bin 呢？

由于数据加载地址是写死的，那意味着必须告知 `mmap` 映射到一个固定的地址，即 .text 的装载地址，否则数据访问就会出错。`mmap` 的第一个参数 addr 配合第三个参数 prot（设置为 `MAP_FIXED`），恰好可以做到。

只是，`mmap` 要求这个地址必须是页对齐的，这个 page size 可以通过 `sysconf(_SC_PAGE_SIZE)` 拿到。

可是，默认链接的时候，.text 段并不是对齐到 page size 的，对齐到 page size 的是 entry addr，还有一个 0x54 的偏移，即 elf header + program header。这个 0x54 末尾的地址不会是 page size 对齐的。

那意味着链接的时候得“做点手脚”，得强制让 .text 对齐到 page size，我们观察到 0x4200000这个地址可以安全使用。

怎么强制修改 .text 的装载地址呢，一个是上节提到的修改 ld.script，另外一个是直接用 ld 的 `-Ttext` 参数：

```
as -o hello.o hello.s
ld -o hello hello.o -Ttext=0x4200000
objcopy -O binary hello hello.absolute.bin
```

```
acrn@acrn:~/Tools/elf2bin/0003$ gcc -o mmap_absolute mmap.absolute.c
acrn@acrn:~/Tools/elf2bin/0003$ ./mmap_absolute
Hello, world
```



### 3. 小结

到这里，ELF转二进制 3 篇文章就完成了，分别讨论了静态嵌入、位置无关和动态加载，接下来还有一篇会讨论，如何动态修改数据地址。