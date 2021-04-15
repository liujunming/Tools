

It is for resolving circular dependences between several libraries (listed between `-(` and `-)`).

> `-(` *archives* `-)` or `--start-group` *archives* `--end-group`
>
> The *archives* should be a list of archive files. They may be either explicit file names, or `-l` options.
>
> The specified archives are searched repeatedly until no new undefined references are created. Normally, an archive is searched only once in the order that it is specified on the command line. If a symbol in that archive is needed to resolve an undefined symbol referred to by an object in an archive that appears later on the command line, the linker would not be able to resolve that reference. By grouping the archives, they all be searched repeatedly until all possible references are resolved.
>
> Using this option has a significant performance cost. It is best to use it only when there are unavoidable circular references between two or more archives.



```
gcc -Wl,--start-group foo.o bar.o -Wl,--end-group
gcc -Wl,--start-group foo.o bar.a -Wl,--end-group
gcc -Wl,--start-group foo.a bar.a -Wl,--end-group
```

So *archives* could be archive files(`*.a`) or object files(`*.o`).

---

Reference:

1. [What are the --start-group and --end-group command line options?](https://stackoverflow.com/questions/5651869/what-are-the-start-group-and-end-group-command-line-options)
2. [ld(1) - Linux man page](https://linux.die.net/man/1/ld)

