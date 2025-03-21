## Desctiption
When I used the  function to handle a specific input, Program received signal SIGILL, Illegal instruction. in comp_distance_value  at /oniguruma/src/regcomp.c:6057

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regcomp.c#L6050-L6057

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/comp_distance_value/comp_distance_value.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/comp_distance_value/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/comp_distance_value/comp_distance_value) and run the following cmd:
```
 $ ./comp_distance_value ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/select_opt_exact/comp_distance_value/comp_distance_value output/default/crashes/id:000000,sig:04,src:000004,time:106066,execs:46759,op:havoc,rep:2
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x00005555556914f4 in comp_distance_value (d1=0x7bfff5709040, d2=0x7bfff5709060, v1=2650, v2=1249946282) at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:6057
6057      v2 *= distance_value(d2);
(gdb) bt
#0  0x00005555556914f4 in comp_distance_value (d1=0x7bfff5709040, d2=0x7bfff5709060, v1=2650, v2=1249946282)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:6057
#1  0x00005555556912d7 in main (argc=2, argv=0x7fffffffda98)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/select_opt_exact/comp_distance_value.c:52
```
