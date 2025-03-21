## Desctiption
When using the  function to handle a specific input, Program received signal SIGILL, Illegal instruction. in node_min_byte_len at /oniguruma/src/regcomp.c:3670
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regcomp.c#L3670

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/tune_quant/node_min_byte_len/node_min_byte_len output/default/crashes/id:000000,sig:04,src:000002,time:7,execs:18,op:quick,pos:1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x0000555555693e5b in node_min_byte_len (node=0x7c6ff6c20020, env=0x7d1ff6c20040) at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:3670
3670        len = ONIGENC_MBC_MINLEN(env->enc);
(gdb) bt
#0  0x0000555555693e5b in node_min_byte_len (node=0x7c6ff6c20020, env=0x7d1ff6c20040)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:3670
#1  0x00005555556914f7 in main (argc=2, argv=0x7fffffffdab8)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/tune_quant/node_min_byte_len.c:58
(gdb) p env->enc
$1 = (OnigEncoding) 0xbebebebebebebebe
```
