## Desctiption
When using the code_to_mbc function to handle a specific input, AddressSanitizer: stack-buffer-overflow in code_to_mbc /oniguruma/src/utf8.c:202

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/utf8.c#L202

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/code_to_mbc/mbc_case_fold.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/code_to_mbc/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/code_to_mbc/mbc_case_fold) and run the following cmd:
```
 $ ./mbc_case_fold ./poc
```

## Detail
### ASAN report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/utf8.c/generate/mbc_case_fold/mbc_case_fold output/default/crashes/id:000000,sig:06,src:000000,time:61,execs:22,op:flip1,pos:0
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==306261==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7bfff5909051 at pc 0x55555566afa8 bp 0x7fffffffd700 sp 0x7fffffffd6f8
WRITE of size 1 at 0x7bfff5909051 thread T0
[Detaching after fork from child process 313303]
    #0 0x55555566afa7 in code_to_mbc /home/ambrose/vsproject/TestLib/oniguruma/src/utf8.c:202:10
    #1 0x55555566b437 in mbc_case_fold /home/ambrose/vsproject/TestLib/oniguruma/src/utf8.c:230:12
    #2 0x55555566c4bb in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/utf8.c/generate/mbc_case_fold.c:37:18
    #3 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #4 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #5 0x555555583434 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/utf8.c/generate/mbc_case_fold/mbc_case_fold+0x2f434) (BuildId: ee6cfd27031c519bc36c80a725510ba36399c6ed)

Address 0x7bfff5909051 is located in stack of thread T0 at offset 81 in frame
    #0 0x55555566bd17 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/utf8.c/generate/mbc_case_fold.c:6

  This frame has 3 object(s):
    [32, 33) 'inputChar' (line 20)
    [48, 56) 'pp' (line 31)
    [80, 81) 'fold' (line 34) <== Memory access at offset 81 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/ambrose/vsproject/TestLib/oniguruma/src/utf8.c:202:10 in code_to_mbc
Shadow bytes around the buggy address:
  0x7bfff5908d80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5908e00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5908e80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5908f00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5908f80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7bfff5909000: f1 f1 f1 f1 01 f2 00 f2 f2 f2[01]f3 00 00 00 00
  0x7bfff5909080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5909100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5909180: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5909200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5909280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==306261==ABORTING
[Inferior 1 (process 306261) exited with code 01]
```
