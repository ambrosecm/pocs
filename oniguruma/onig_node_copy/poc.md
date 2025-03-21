## Desctiption
When using the onig_node_copy function to handle a specific input, Program received signal SIGILL, Illegal instruction. in onig_node_copy at /oniguruma/src/regparse.c:2302
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regparse.c#L2294-L2302

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/tune_look_behind/onig_node_copy/onig_node_copy output/default/crashes/id:000000,sig:04,src:000001,time:271,execs:128,op:havoc,rep:15
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x00005555557a19d5 in onig_node_copy (rcopy=0x7bfff5909030, from=0x0) at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:2302
2302      switch (ND_TYPE(from)) {
(gdb) bt
#0  0x00005555557a19d5 in onig_node_copy (rcopy=0x7bfff5909030, from=0x0)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:2302
#1  0x0000555555691101 in main (argc=2, argv=0x7fffffffdab8)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/tune_look_behind/onig_node_copy.c:35
```
