```
gcc -c test.c
objcopy -O binary -j .text test.o binfile
```



You can make sure it's correct with `objdump`:

```
acrn@acrn:~/Tools/objcopy/0002-raw-binary$ objdump -d test.o

test.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <f>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   89 7d ec                mov    %edi,-0x14(%rbp)
   7:   8b 45 ec                mov    -0x14(%rbp),%eax
   a:   0f af 45 ec             imul   -0x14(%rbp),%eax
   e:   89 45 fc                mov    %eax,-0x4(%rbp)
  11:   8b 45 fc                mov    -0x4(%rbp),%eax
  14:   83 c0 02                add    $0x2,%eax
  17:   5d                      pop    %rbp
  18:   c3                      retq
```

And compare it with the binary file:

```
acrn@acrn:~/Tools/objcopy/0002-raw-binary$ hexdump -C binfile
00000000  55 48 89 e5 89 7d ec 8b  45 ec 0f af 45 ec 89 45  |UH...}..E...E..E|
00000010  fc 8b 45 fc 83 c0 02 5d  c3                       |..E....].|
00000019
```





---

Reference:

1. [Is there a way to get gcc to output raw binary?](https://stackoverflow.com/questions/1647359/is-there-a-way-to-get-gcc-to-output-raw-binary)