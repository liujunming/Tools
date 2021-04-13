`gcc -o main_test test.c`

```
acrn@acrn:~/Tools/gcc/change_entry_func$ ./main_test
Entry is the default main!
```



`gcc -Wl,--entry=test -o test test.c` or
`gcc -Wl,-etest -o test test.c`

```
acrn@acrn:~/Tools/gcc/change_entry_func$ ./test
Entry is test function!
```



---

Reference:

1. [How to change entry point of C program with gcc?](https://stackoverflow.com/questions/7494244/how-to-change-entry-point-of-c-program-with-gcc)

