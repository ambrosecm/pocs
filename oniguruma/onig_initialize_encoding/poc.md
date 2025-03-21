## Desctiption
When I used the onig_initialize_encoding function to handle a specific input, Program received signal SIGILL, Illegal instruction in onig_initialize_encoding at /oniguruma/src/regenc.c:115

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regenc.c#L109-L115

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_initialize_encoding/onig_initialize.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_initialize_encoding/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_initialize_encoding/onig_initialize) and run the following cmd:
```
 $ ./onig_initialize ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/onig_reg_init/onig_initialize/onig_initialize output/default/crashes/id:000000,sig:04,src:000002,time:519,execs:182,op:havoc,rep:2
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x000055555576da29 in onig_initialize_encoding (enc=0x7) at /home/ambrose/vsproject/TestLib/oniguruma/src/regenc.c:115
115           ONIGENC_IS_ASCII_COMPATIBLE_ENCODING(enc)) {
(gdb) bt
#0  0x000055555576da29 in onig_initialize_encoding (enc=0x7)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regenc.c:115
#1  0x00005555556880d7 in onig_initialize (encodings=0x7bfff5809020, n=1)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:7779
#2  0x0000555555691113 in main (argc=2, argv=0x7fffffffdab8)
    at output/oniguruma_deepseek24/harness/code/regcomp.c/onig_reg_init/onig_initialize.c:30
(gdb) p enc
$1 = (OnigEncoding) 0x7
```
