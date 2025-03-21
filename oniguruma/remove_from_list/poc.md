## Desctiption
When I used the remove_from_list function to handle a specific input, Program received signal SIGILL, Illegal instruction. in remove_from_list at /oniguruma/src/regcomp.c:4365

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regcomp.c#L4362-L4365

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/remove_from_list/remove_from_list.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/remove_from_list/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/remove_from_list/remove_from_list) and run the following cmd:
```
 $ ./remove_from_list ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/reduce_string_list/remove_from_list/remove_from_list output/default/crashes/id:000000,sig:04,src:000000,time:347,execs:178,op:havoc,rep:3
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x0000555555691258 in remove_from_list (prev=0x111, a=0xb) at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:4365
4365      if (ND_CDR(prev) != a) return ;
(gdb) bt
#0  0x0000555555691258 in remove_from_list (prev=0x111, a=0xb)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:4365
#1  0x000055555569112d in main (argc=2, argv=0x7fffffffdaa8)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/reduce_string_list/remove_from_list.c:33
```
