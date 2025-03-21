## Desctiption
When using the node_list_add function to handle a specific input, Program received signal SIGILL, Illegal instruction. in node_list_add at /oniguruma/src/regcomp.c:405

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regcomp.c#L396-L405

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/unravel_cf_node_add/node_list_add/node_list_add output/default/crashes/id:000000,sig:04,src:000000,time:7490,execs:2415,op:havoc,rep:23
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x00005555556914f2 in node_list_add (list=0x333, x=0x333333) at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:405
405         while (IS_NOT_NULL(ND_CDR(list)))
(gdb) bt
#0  0x00005555556914f2 in node_list_add (list=0x333, x=0x333333)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:405
#1  0x00005555556911f4 in main (argc=2, argv=0x7fffffffdaa8)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/unravel_cf_node_add/node_list_add.c:38
```
