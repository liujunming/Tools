```
gcc -c test.c -o test.o
objcopy --redefine-sym entry=main test.o
gcc test.o -o test
./test
```





---

Reference:

1. [How to change entry point of C program with gcc?](https://stackoverflow.com/a/34277775/15530503)