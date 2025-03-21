## Desctiption
When I used the onig_free function to handle a specific input, AddressSanitizer: attempting free on address which was not malloc()-ed in ops_free /oniguruma/src/regcomp.c:162

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regcomp.c#L7345-L7372
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regcomp.c#L162

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_free/parse_and_tune.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_free/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_free/parse_and_tune) and run the following cmd:
```
 $ ./parse_and_tune ./poc
```

## Detail
### ASAN report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/onig_compile/parse_and_tune/parse_and_tune output/default/crashes/id:000000,sig:06,src:000000,time:17354,execs:5065,op:havoc,rep:2
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==777244==ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed: 0x7c2ff6a20346 in thread T0
[Detaching after fork from child process 785784]
    #0 0x555555628186 in free (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/onig_compile/parse_and_tune/parse_and_tune+0xd4186) (BuildId: ef028c53297e46824b52ee27794e2fdd01f4aacd)
    #1 0x55555566e97e in ops_free /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:162:9
    #2 0x55555566cb5b in onig_free_body /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:7349:5
    #3 0x5555556704b5 in onig_free /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:7369:5
    #4 0x555555691565 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regcomp.c/onig_compile/parse_and_tune.c:47:5
    #5 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #6 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #7 0x555555585434 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/onig_compile/parse_and_tune/parse_and_tune+0x31434) (BuildId: ef028c53297e46824b52ee27794e2fdd01f4aacd)

0x7c2ff6a20346 is located 6 bytes inside of 26-byte region [0x7c2ff6a20340,0x7c2ff6a2035a)
freed by thread T0 here:
    #0 0x555555628186 in free (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/onig_compile/parse_and_tune/parse_and_tune+0xd4186) (BuildId: ef028c53297e46824b52ee27794e2fdd01f4aacd)
    #1 0x55555566e97e in ops_free /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:162:9
    #2 0x55555566cb5b in onig_free_body /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:7349:5
    #3 0x5555556704b5 in onig_free /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:7369:5
    #4 0x555555691565 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regcomp.c/onig_compile/parse_and_tune.c:47:5
    #5 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

previously allocated by thread T0 here:
    #0 0x555555628424 in malloc (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/onig_compile/parse_and_tune/parse_and_tune+0xd4424) (BuildId: ef028c53297e46824b52ee27794e2fdd01f4aacd)
    #1 0x555555683df4 in ops_make_string_pool /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:265:26
    #2 0x5555556734f1 in onig_compile /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:7626:9
    #3 0x5555556887a3 in onig_new /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:7756:7
    #4 0x5555556913ae in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regcomp.c/onig_compile/parse_and_tune.c:34:13
    #5 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: bad-free (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/onig_compile/parse_and_tune/parse_and_tune+0xd4186) (BuildId: ef028c53297e46824b52ee27794e2fdd01f4aacd) in free
==777244==ABORTING
[Inferior 1 (process 777244) exited with code 01]
```
