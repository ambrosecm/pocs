## Desctiption
When using the is_ancestor_node function to handle a specific input, Program received signal SIGILL, Illegal instruction. in is_ancestor_node at /oniguruma/src/regcomp.c:3893

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regcomp.c#L3888-L3893

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/is_ancestor_node/is_ancestor_node.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/is_ancestor_node/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/is_ancestor_node/is_ancestor_node) and run the following cmd:
```
 $ ./is_ancestor_node ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/set_empty_status_check_trav/is_ancestor_node/is_ancestor_node output/default/crashes/id:000000,sig:04,src:000000,time:125,execs:76,op:havoc,rep:3
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x00005555556912a8 in is_ancestor_node (node=0xffffffffffffffff, me=0x131) at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:3893
3893      while ((parent = ND_PARENT(me)) != NULL_NODE) {
(gdb) bt
#0  0x00005555556912a8 in is_ancestor_node (node=0xffffffffffffffff, me=0x131)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:3893
#1  0x0000555555691100 in main (argc=2, argv=0x7fffffffda88)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/set_empty_status_check_trav/is_ancestor_node.c:33
```
