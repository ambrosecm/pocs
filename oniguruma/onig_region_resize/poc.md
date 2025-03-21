## Desctiption
When using the onig_region_resize function to handle a specific input, Program received signal SIGSEGV, Segmentation fault. in onig_region_resize at /oniguruma/src/regexec.c:920


## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file]()

## How to trigger
Download the [poc file]() , [program]() and run the following cmd:
```
 $ ./ ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regexec.c/onig_regset_search_with_param/onig_region_resize_clear/onig_region_resize_clear output/default/crashes/id:000000,sig:11,src:000000,time:571,execs:91,op:havoc,rep:8
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x000055555566cf76 in onig_region_resize (region=0x8, n=20) at /home/ambrose/vsproject/TestLib/oniguruma/src/regexec.c:920
920       region->num_regs = n;
(gdb) bt
#0  0x000055555566cf76 in onig_region_resize (region=0x8, n=20)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regexec.c:920
#1  0x0000555555683a63 in onig_region_resize_clear (region=0x8, n=20)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regexec.c:952
#2  0x0000555555705f3e in main (argc=2, argv=0x7fffffffda58)
    at output/oniguruma_deepseek24/harness/code/regexec.c/onig_regset_search_with_param/onig_region_resize_clear.c:32
```
