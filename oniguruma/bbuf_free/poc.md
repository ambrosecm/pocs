## Desctiption
When I used the bbuf_free function to handle a specific input, Program received signal SIGILL, Illegal instruction. in bbuf_free at /oniguruma/src/regparse.c:352


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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/reduce_string_list/onig_node_free/onig_node_free output/default/crashes/id:000000,sig:04,src:000002,time:23,execs:19,op:quick,pos:1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x00005555557bc6f0 in bbuf_free (bbuf=0xbebebebebebebebe) at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:352
352         if (IS_NOT_NULL(bbuf->p)) xfree(bbuf->p);
(gdb) bt
#0  0x00005555557bc6f0 in bbuf_free (bbuf=0xbebebebebebebebe)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:352
#1  0x00005555557a030d in node_free_body (node=0x7c6ff6c20020)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:2217
#2  0x000055555579ee06 in onig_node_free (node=0x7c6ff6c20020)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:2267
#3  0x000055555569133c in main (argc=2, argv=0x7fffffffdab8)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/reduce_string_list/onig_node_free.c:40
```
