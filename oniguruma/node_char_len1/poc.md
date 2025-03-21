## Desctiption
When I used the node_char_len1 function to handle a specific input. Program received signal SIGILL, Illegal instruction in node_char_len1 at /oniguruma/src/regcomp.c:642


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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/node_char_len/node_char_len1/node_char_len1 output/default/crashes/id:000000,sig:04,src:000000,time:126,execs:76,op:havoc,rep:1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x000055555569145d in node_char_len1 (node=0x0, reg=0x0, ci=0x7bfff5709030, env=0x0, level=1) at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:642
642       switch (ND_TYPE(node)) {
(gdb) bt
#0  0x000055555569145d in node_char_len1 (node=0x0, reg=0x0, ci=0x7bfff5709030, env=0x0, level=1)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:642
#1  0x0000555555691163 in main (argc=2, argv=0x7fffffffdab8)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/node_char_len/node_char_len1.c:38
```
