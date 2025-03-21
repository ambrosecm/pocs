## Desctiption
When using the add_ctype_to_cc_by_range function to handle a specific input, AddressSanitizer: stack-buffer-overflow in add_ctype_to_cc_by_range /oniguruma/src/regparse.c:6459

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regparse.c#L6446-L6459

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/add_ctype_to_cc_by_range/add_ctype_to_cc_by_range output/default/crashes/id:000000,sig:06,src:000002,time:173,execs:50,op:havoc,rep:2
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==989417==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7bfff5809078 at pc 0x55555569a665 bp 0x7fffffffd550 sp 0x7fffffffd548
READ of size 4 at 0x7bfff5809078 thread T0
[Detaching after fork from child process 997824]
    #0 0x55555569a664 in add_ctype_to_cc_by_range /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:6459:17
    #1 0x55555569a079 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regparse.c/generate/add_ctype_to_cc_by_range.c:39:5
    #2 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #3 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #4 0x555555585464 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/add_ctype_to_cc_by_range/add_ctype_to_cc_by_range+0x31464) (BuildId: 7d820f9af788376ea100b8d2ae0f18272b812768)

Address 0x7bfff5809078 is located in stack of thread T0 at offset 120 in frame
    #0 0x555555699967 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regparse.c/generate/add_ctype_to_cc_by_range.c:8

  This frame has 7 object(s):
    [32, 36) 'from' (line 21)
    [48, 52) 'to' (line 21)
    [64, 68) 'not' (line 21)
    [80, 84) 'ctype' (line 22)
    [96, 100) 'sb_out' (line 24)
    [112, 120) 'mbr' (line 25) <== Memory access at offset 120 overflows this variable
    [144, 208) 'cc' (line 26)
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:6459:17 in add_ctype_to_cc_by_range
Shadow bytes around the buggy address:
  0x7bfff5808d80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5808e00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5808e80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5808f00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5808f80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7bfff5809000: f1 f1 f1 f1 04 f2 04 f2 04 f2 04 f2 04 f2 00[f2]
  0x7bfff5809080: f2 f2 00 00 00 00 00 00 00 00 f3 f3 f3 f3 f3 f3
  0x7bfff5809100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5809180: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5809200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5809280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==989417==ABORTING
[Inferior 1 (process 989417) exited with code 01]
```
