
## Desctiption
When using the unravel_cf_look_behind_add function to handle a specific input, AddressSanitizer: stack-buffer-overflow in unravel_cf_look_behind_add /oniguruma/src/regcomp.c:4925

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regcomp.c#L4915-L4925

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/unravel_cf_look_behind_add/unravel_cf_look_behind_add.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/unravel_cf_look_behind_add/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/unravel_cf_look_behind_add/unravel_cf_look_behind_add) and run the following cmd:
```
 $ ./unravel_cf_look_behind_add ./poc
```

## Detail
### ASAN report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/unravel_case_fold_string/unravel_cf_look_behind_add/unravel_cf_look_behind_add output/default/crashes/id:000000,sig:06,src:000002,time:43,execs:38,op:flip1,pos:1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==1519417==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7bfff5b09174 at pc 0x555555691869 bp 0x7fffffffd5f0 sp 0x7fffffffd5e8
READ of size 4 at 0x7bfff5b09174 thread T0
[Detaching after fork from child process 1527881]
    #0 0x555555691868 in unravel_cf_look_behind_add /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:4925:15
    #1 0x5555556911fa in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regcomp.c/unravel_case_fold_string/unravel_cf_look_behind_add.c:36:13
    #2 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #3 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #4 0x555555585434 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/unravel_case_fold_string/unravel_cf_look_behind_add/unravel_cf_look_behind_add+0x31434) (BuildId: cefcb22fff0169f61b84f1c12e9e775ca6fb6564)

Address 0x7bfff5b09174 is located in stack of thread T0 at offset 372 in frame
    #0 0x555555690b37 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regcomp.c/unravel_case_fold_string/unravel_cf_look_behind_add.c:6

  This frame has 4 object(s):
    [32, 40) 'list' (line 20)
    [64, 72) 'sn' (line 21)
    [96, 100) 'n' (line 22)
    [112, 372) 'items' (line 23) <== Memory access at offset 372 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/ambrose/vsproject/TestLib/oniguruma/src/regcomp.c:4925:15 in unravel_cf_look_behind_add
Shadow bytes around the buggy address:
  0x7bfff5b08e80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b08f00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b08f80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09000: f1 f1 f1 f1 00 f2 f2 f2 00 f2 f2 f2 04 f2 00 00
  0x7bfff5b09080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7bfff5b09100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00[04]f3
  0x7bfff5b09180: f3 f3 f3 f3 f3 f3 f3 f3 00 00 00 00 00 00 00 00
  0x7bfff5b09200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09300: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09380: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==1519417==ABORTING
[Inferior 1 (process 1519417) exited with code 01]
```
