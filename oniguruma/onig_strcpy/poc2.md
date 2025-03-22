## Desctiption
When using the onig_strcpy function to handle a specific input, AddressSanitizer: heap-buffer-overflow in onig_strcpy /oniguruma/src/regparse.c:479
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regparse.c#L474-L479

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_strcpy/strcat_capa_from_static.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_strcpy/poc2) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/onig_strcpy/strcat_capa_from_static) and run the following cmd:
```
 $ ./strcat_capa_from_static ./poc2
```

## Detail
### ASAN report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/strcat_capa_from_static/strcat_capa_from_static output/default/crashes/id:000000,sig:06,src:000000,time:195,execs:54,op:quick,pos:13
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==2025379==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x7c1ff6a20013 at pc 0x55555562623e bp 0x7fffffffd790 sp 0x7fffffffcf50
WRITE of size 4 at 0x7c1ff6a20013 thread T0
[Detaching after fork from child process 2032231]
    #0 0x55555562623d in __asan_memcpy (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/strcat_capa_from_static/strcat_capa_from_static+0xd223d) (BuildId: bf8fbd9be4a262e1aeff28bd156097980154ce79)
    #1 0x55555566c2eb in onig_strcpy /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:479:5
    #2 0x555555687848 in strcat_capa_from_static /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:538:3
    #3 0x55555569a1f3 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regparse.c/generate/strcat_capa_from_static.c:41:5
    #4 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #5 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #6 0x555555585464 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/strcat_capa_from_static/strcat_capa_from_static+0x31464) (BuildId: bf8fbd9be4a262e1aeff28bd156097980154ce79)

0x7c1ff6a20013 is located 0 bytes after 3-byte region [0x7c1ff6a20010,0x7c1ff6a20013)
allocated by thread T0 here:
    #0 0x555555628454 in malloc (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/strcat_capa_from_static/strcat_capa_from_static+0xd4454) (BuildId: bf8fbd9be4a262e1aeff28bd156097980154ce79)
    #1 0x5555556877e8 in strcat_capa_from_static /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:536:16
    #2 0x55555569a1f3 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regparse.c/generate/strcat_capa_from_static.c:41:5
    #3 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: heap-buffer-overflow (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/strcat_capa_from_static/strcat_capa_from_static+0xd223d) (BuildId: bf8fbd9be4a262e1aeff28bd156097980154ce79) in __asan_memcpy
Shadow bytes around the buggy address:
  0x7c1ff6a1fd80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6a1fe00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6a1fe80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6a1ff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6a1ff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7c1ff6a20000: fa fa[03]fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6a20080: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6a20100: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6a20180: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6a20200: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x7c1ff6a20280: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
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
==2025379==ABORTING
[Inferior 1 (process 2025379) exited with code 01]
```
