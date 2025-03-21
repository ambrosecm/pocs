## Desctiption
When I used the onig_reduce_nested_quantifier function to handle a specific input, Program received signal SIGILL, Illegal instruction. in onig_reduce_nested_quantifier at /oniguruma/src/regparse.c:4433

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regparse.c#L4423-L4433

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_reduce_nested_quantifier/onig_reduce_nested_quantifier.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_reduce_nested_quantifier/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_reduce_nested_quantifier/onig_reduce_nested_quantifier) and run the following cmd:
```
 $ ./onig_reduce_nested_quantifier ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/make_named_capture_number_map/onig_reduce_nested_quantifier/onig_reduce_nested_quantifier output/default/crashes/id:000000,sig:04,src:000000,time:622,execs:280,op:havoc,rep:11
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x00005555557aaf6a in onig_reduce_nested_quantifier (pnode=0x7c6ff6a20020) at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:4433
4433      c = QUANT_(cnode);
(gdb) bt
#0  0x00005555557aaf6a in onig_reduce_nested_quantifier (pnode=0x7c6ff6a20020)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:4433
#1  0x0000555555691348 in main (argc=2, argv=0x7fffffffd9c8)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/make_named_capture_number_map/onig_reduce_nested_quantifier.c:43
(gdb) p code
No symbol "code" in current context.
(gdb) p cnode
$1 = (Node *) 0xbebebebebebebebe
```
