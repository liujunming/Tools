`gcc test.c -o test`

```
acrn@acrn:~/Tools/gcc/0002-Ttext-segment_usage$ nm test
0000000000600e28 d _DYNAMIC
0000000000601000 d _GLOBAL_OFFSET_TABLE_
00000000004005d0 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 w _Jv_RegisterClasses
0000000000400708 r __FRAME_END__
00000000004005e4 r __GNU_EH_FRAME_HDR
0000000000600e20 d __JCR_END__
0000000000600e20 d __JCR_LIST__
0000000000601038 D __TMC_END__
0000000000601038 B __bss_start
0000000000601028 D __data_start
00000000004004e0 t __do_global_dtors_aux
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
0000000000601030 D __dso_handle
0000000000600e10 t __frame_dummy_init_array_entry
                 w __gmon_start__
0000000000600e18 t __init_array_end
0000000000600e10 t __init_array_start
00000000004005c0 T __libc_csu_fini
0000000000400550 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
0000000000601038 D _edata
0000000000601040 B _end
00000000004005c4 T _fini
00000000004003c8 T _init
0000000000400430 T _start
0000000000601038 b completed.7594
0000000000601028 W data_start
0000000000400460 t deregister_tm_clones
0000000000400500 t frame_dummy
0000000000400526 T main
                 U puts@@GLIBC_2.2.5
00000000004004a0 t register_tm_clones
```





`gcc -Wl,-Ttext-segment,0x4200000 test.c -o test`

```
acrn@acrn:~/Tools/gcc/0002-Ttext-segment_usage$ nm test
0000000004400e28 d _DYNAMIC
0000000004401000 d _GLOBAL_OFFSET_TABLE_
00000000042005d0 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 w _Jv_RegisterClasses
0000000004200708 r __FRAME_END__
00000000042005e4 r __GNU_EH_FRAME_HDR
0000000004400e20 d __JCR_END__
0000000004400e20 d __JCR_LIST__
0000000004401038 D __TMC_END__
0000000004401038 B __bss_start
0000000004401028 D __data_start
00000000042004e0 t __do_global_dtors_aux
0000000004400e18 t __do_global_dtors_aux_fini_array_entry
0000000004401030 D __dso_handle
0000000004400e10 t __frame_dummy_init_array_entry
                 w __gmon_start__
0000000004400e18 t __init_array_end
0000000004400e10 t __init_array_start
00000000042005c0 T __libc_csu_fini
0000000004200550 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
0000000004401038 D _edata
0000000004401040 B _end
00000000042005c4 T _fini
00000000042003c8 T _init
0000000004200430 T _start
0000000004401038 b completed.7594
0000000004401028 W data_start
0000000004200460 t deregister_tm_clones
0000000004200500 t frame_dummy
0000000004200526 T main
                 U puts@@GLIBC_2.2.5
00000000042004a0 t register_tm_clones
```



---

Reference:

1. [What does SEGMENT_START(“text-segment”, 0x400000) represent?](https://stackoverflow.com/questions/55270381/what-does-segment-starttext-segment-0x400000-represent)

