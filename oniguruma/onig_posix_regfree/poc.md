## Desctiption
When using the onig_posix_regfree function to handle a specific input, Program received signal SIGSEGV, Segmentation fault. in onig_posix_regfree at /oniguruma/src/regposix.c:257
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regposix.c#L254-L257

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_posix_regfree/onig_posix_regfree.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_posix_regfree/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_posix_regfree/onig_posix_regfree) and run the following cmd:
```
 $ ./onig_posix_regfree ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regposix.c/generate/onig_posix_regfree/onig_posix_regfree output/default/crashes/id:000000,sig:11,src:000000,time:214,execs:101,op:havoc,rep:1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x00007ffff7f2e2ba in onig_free_body () from /lib/x86_64-linux-gnu/libonig.so.5
(gdb) bt
#0  0x00007ffff7f2e2ba in onig_free_body () from /lib/x86_64-linux-gnu/libonig.so.5
#1  0x00007ffff7f2e482 in onig_free () from /lib/x86_64-linux-gnu/libonig.so.5
#2  0x000055555566d2b0 in onig_posix_regfree (reg=0x7bfff5909020)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regposix.c:257
#3  0x000055555566e7da in main (argc=2, argv=0x7fffffffdab8)
    at output/oniguruma_deepseek24/harness/code/regposix.c/generate/onig_posix_regfree.c:32
```
