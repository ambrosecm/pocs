## Desctiption
When using the onigenc_get_prev_char_head function to handle a specific input, Program received signal SIGSEGV, Segmentation fault in onigenc_get_prev_char_head at /oniguruma/src/regenc.c:200

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regenc.c#L194-L200

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onigenc_get_prev_char_head/onigenc_get_prev_char_head.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onigenc_get_prev_char_head/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onigenc_get_prev_char_head/onigenc_get_prev_char_head) and run the following cmd:
```
 $ ./onigenc_get_prev_char_head ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regexec.c/backward_search/onigenc_get_prev_char_head/onigenc_get_prev_char_head output/default/crashes/id:000000,sig:11,src:000001,time:296,execs:89,op:havoc,rep:8
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x00007ffff7f3b24c in ?? () from /lib/x86_64-linux-gnu/libonig.so.5
(gdb) bt
#0  0x00007ffff7f3b24c in ?? () from /lib/x86_64-linux-gnu/libonig.so.5
#1  0x000055555571c416 in onigenc_get_prev_char_head (enc=0x7ffff7f9c500 <OnigEncodingUTF8>, start=0x0, 
    s=0x94b90 <error: Cannot access memory at address 0x94b90>)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regenc.c:200
#2  0x0000555555705f71 in main (argc=2, argv=0x7fffffffda78)
    at output/oniguruma_deepseek24/harness/code/regexec.c/backward_search/onigenc_get_prev_char_head.c:34
```
