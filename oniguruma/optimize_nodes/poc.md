## Desctiption
When I used the  function to handle a specific input, Program received signal SIGILL, Illegal instruction. in optimize_nodes at /oniguruma/src/regcomp.c:6635

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regcomp.c#L6622-L6635

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/optimize_nodes/copy_opt_map/copy_opt_map output/default/crashes/id:000000,sig:04,src:000001,time:303,execs:145,op:havoc,rep:6
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x00005555556918b8 in optimize_nodes (node=0x0, opt=0x7bfff5a09070, env=0x7bfff5a09030) at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:6635
6635      switch (ND_TYPE(node)) {
(gdb) bt
#0  0x00005555556918b8 in optimize_nodes (node=0x0, opt=0x7bfff5a09070, env=0x7bfff5a09030)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:6635
#1  0x00005555556912c2 in main (argc=2, argv=0x7fffffffdac8)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/optimize_nodes/copy_opt_map.c:42
```
