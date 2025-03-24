## Desctiption
When using the tdefl_calculate_minimum_redundancy function to handle a specific input. AddressSanitizer: heap-buffer-overflow in tdefl_calculate_minimum_redundancy /LuPng/miniz.h:2150
https://github.com/jansol/LuPng/blob/5ec546e0d16d0fb9316967949b2676227eb93736/miniz.h#L2128-L2150

## Test Environment
Ubuntu 22.04.1, 64bit
LuPng(commits on Aug 28, 2021 master https://github.com/jansol/LuPng/commit/5ec546e0d16d0fb9316967949b2676227eb93736)
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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/crashes/miniz.h/generate/tdefl_calculate_minimum_redundancy/tdefl_calculate_minimum_redundancy output/default/crashes/id:000000,sig:06,src:000000,time:3315,execs:1095,op:havoc,rep:1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==3213828==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x7c1ff6c2001c at pc 0x555555782393 bp 0x7fffffffd5b0 sp 0x7fffffffd5a8
READ of size 2 at 0x7c1ff6c2001c thread T0
[Detaching after fork from child process 3213831]
    #0 0x555555782392 in tdefl_calculate_minimum_redundancy /home/ambrose/vsproject/TestLib/LuPng/miniz.h:2150:66
    #1 0x555555780c2a in main /home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/harness/code/miniz.h/generate/tdefl_calculate_minimum_redundancy.c:49:5
    #2 0x7ffff7c29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #3 0x7ffff7c29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #4 0x555555584434 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/crashes/miniz.h/generate/tdefl_calculate_minimum_redundancy/tdefl_calculate_minimum_redundancy+0x30434) (BuildId: 1eae171a7f12a55c90564c99ea9e602e5f4b3383)

0x7c1ff6c2001c is located 0 bytes after 12-byte region [0x7c1ff6c20010,0x7c1ff6c2001c)
allocated by thread T0 here:
    #0 0x555555627424 in malloc (/home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/crashes/miniz.h/generate/tdefl_calculate_minimum_redundancy/tdefl_calculate_minimum_redundancy+0xd3424) (BuildId: 1eae171a7f12a55c90564c99ea9e602e5f4b3383)
    #1 0x555555780925 in main /home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/harness/code/miniz.h/generate/tdefl_calculate_minimum_redundancy.c:28:41
    #2 0x7ffff7c29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/ambrose/vsproject/TestLib/LuPng/miniz.h:2150:66 in tdefl_calculate_minimum_redundancy
Shadow bytes around the buggy address:
  0x7c1ff6c1fd80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1fe00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1fe80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1ff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1ff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7c1ff6c20000: fa fa 00[04]fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6c20080: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6c20100: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6c20180: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6c20200: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6c20280: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
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
==3213828==ABORTING
[Inferior 1 (process 3213828) exited with code 01]
```
