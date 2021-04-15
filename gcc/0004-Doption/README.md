#### D选项

D选项是用来在使用gcc/g++编译的时候定义宏的。

- gcc -DDEBUG or gcc -D DEBUG

-D 后面直接跟宏命，相当于定义这个宏，默认这个宏的内容是1

- gcc -DNAME=Peter

-D 后面跟 key=value 表示定义key这个宏，它的内容是value




```
acrn@acrn:~/Tools/gcc/0004-Doption$ gcc -D DEBUG name_test.c && ./a.out
Debug run
acrn@acrn:~/Tools/gcc/0004-Doption$ gcc -DDEBUG name_test.c && ./a.out
Debug run
acrn@acrn:~/Tools/gcc/0004-Doption$ gcc name_test.c && ./a.out
Release run
```



```
acrn@acrn:~/Tools/gcc/0004-Doption$ gcc -D DEBUG=0 name_test.c && ./a.out
Debug run
acrn@acrn:~/Tools/gcc/0004-Doption$ gcc -D DEBUG=1 name_test.c && ./a.out
Debug run
acrn@acrn:~/Tools/gcc/0004-Doption$ gcc -D DEBUG=0 definition_test.c  && ./a.out
Release run
acrn@acrn:~/Tools/gcc/0004-Doption$ gcc -D DEBUG=1 definition_test.c  && ./a.out
Debug run
```

---
Reference:

1. [Options Controlling the Preprocessor](https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html)

1. [gcc -D 选项](https://blog.csdn.net/sdoyuxuan/article/details/85050553)
2. [gcc -D option flag](https://www.rapidtables.com/code/linux/gcc/gcc-d.html)