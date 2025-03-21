## Desctiption
When using the and_code_range1 function to handle a specific input,  AddressSanitizer: stack-buffer-overflow in and_code_range1 /oniguruma/src/regparse.c:4117
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regparse.c#L4109-L4117

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
### ASAN report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/and_code_range1/and_code_range1 output/default/crashes/id:000000,sig:06,src:000000,time:348,execs:70,op:flip2,pos:1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==3828407==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7bfff5809088 at pc 0x55555569a4f7 bp 0x7fffffffd7e0 sp 0x7fffffffd7d8
READ of size 4 at 0x7bfff5809088 thread T0
[Detaching after fork from child process 3835126]
    #0 0x55555569a4f6 in and_code_range1 /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:4117:13
    #1 0x555555699fd3 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regparse.c/generate/and_code_range1.c:38:18
    #2 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #3 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #4 0x555555585464 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/and_code_range1/and_code_range1+0x31464) (BuildId: 40bfa325e49af6c7b4adb2b41a94f86c7cabd33a)

Address 0x7bfff5809088 is located in stack of thread T0 at offset 136 in frame
    #0 0x555555699967 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regparse.c/generate/and_code_range1.c:8

  This frame has 6 object(s):
    [32, 36) 'start1' (line 22)
    [48, 52) 'end1' (line 22)
    [64, 68) 'start2' (line 22)
    [80, 84) 'end2' (line 22)
    [96, 104) 'pbuf' (line 33)
    [128, 136) 'data' (line 34) <== Memory access at offset 136 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:4117:13 in and_code_range1
Shadow bytes around the buggy address:
  0x7bfff5808e00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5808e80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5808f00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5808f80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5809000: f1 f1 f1 f1 04 f2 04 f2 04 f2 04 f2 00 f2 f2 f2
=>0x7bfff5809080: 00[f3]f3 f3 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5809100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5809180: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5809200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5809280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5809300: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==3828407==ABORTING
[Inferior 1 (process 3828407) exited with code 01]
```
