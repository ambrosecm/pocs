## Desctiption
When using the onigenc_str_bytelen_null function to handle a specific input, AddressSanitizer: stack-buffer-overflow in onigenc_str_bytelen_null /oniguruma/src/regenc.c:270
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regenc.c#L263-L270

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onigenc_str_bytelen_null/onigenc_str_bytelen_null.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onigenc_str_bytelen_null/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onigenc_str_bytelen_null/onigenc_str_bytelen_null) and run the following cmd:
```
 $ ./onigenc_str_bytelen_null ./poc
```

## Detail
### ASAN report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regenc.c/generate/onigenc_str_bytelen_null/onigenc_str_bytelen_null output/default/crashes/id:000000,sig:06,src:000005,time:601351,execs:159062,op:havoc,rep:62
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==113772==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7bfff5b09421 at pc 0x55555566e0fd bp 0x7fffffffd7a0 sp 0x7fffffffd798
READ of size 1 at 0x7bfff5b09421 thread T0
[Detaching after fork from child process 122514]
    #0 0x55555566e0fc in onigenc_str_bytelen_null /home/ambrose/vsproject/TestLib/oniguruma/src/regenc.c:270:9
    #1 0x55555567c377 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regenc.c/generate/onigenc_str_bytelen_null.c:40:18
    #2 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #3 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #4 0x555555583404 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regenc.c/generate/onigenc_str_bytelen_null/onigenc_str_bytelen_null+0x2f404) (BuildId: 73f923b8750ebf8130cc10eb671c2e7adfd24d85)

Address 0x7bfff5b09421 is located in stack of thread T0 at offset 1057 in frame
    #0 0x55555567bbc7 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regenc.c/generate/onigenc_str_bytelen_null.c:9

  This frame has 1 object(s):
    [32, 1056) 'input' (line 23) <== Memory access at offset 1057 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/ambrose/vsproject/TestLib/oniguruma/src/regenc.c:270:9 in onigenc_str_bytelen_null
Shadow bytes around the buggy address:
  0x7bfff5b09180: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09300: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09380: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7bfff5b09400: 00 00 00 00[f3]f3 f3 f3 f3 f3 f3 f3 f3 f3 f3 f3
  0x7bfff5b09480: f3 f3 f3 f3 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09500: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09580: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09600: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5b09680: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==113772==ABORTING
[Inferior 1 (process 113772) exited with code 01]
```
