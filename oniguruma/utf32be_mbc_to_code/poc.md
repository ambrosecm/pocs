## Desctiption
When using the utf32be_mbc_to_code function to handle a specific input. AddressSanitizer: heap-buffer-overflow in utf32be_mbc_to_code /oniguruma/src/utf32_be.c:72
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/utf32_be.c#L67-L72

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/utf32_be.c/utf32be_mbc_case_fold/onigenc_unicode_mbc_case_fold/onigenc_unicode_mbc_case_fold output/default/crashes/id:000000,sig:06,src:000000,time:68,execs:19,op:havoc,rep:7
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==1313179==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x7c1ff6c20012 at pc 0x55555566a3d6 bp 0x7fffffffd760 sp 0x7fffffffd758
READ of size 1 at 0x7c1ff6c20012 thread T0
[Detaching after fork from child process 1322017]
    #0 0x55555566a3d5 in utf32be_mbc_to_code /home/ambrose/vsproject/TestLib/oniguruma/src/utf32_be.c:72:65
    #1 0x7ffff7f3fd2e in onigenc_unicode_mbc_case_fold (/lib/x86_64-linux-gnu/libonig.so.5+0x33d2e) (BuildId: 2159df0f13db9e480831d33c54f1fd97489724c3)
    #2 0x55555566c286 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/utf32_be.c/utf32be_mbc_case_fold/onigenc_unicode_mbc_case_fold.c:41:5
    #3 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #4 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #5 0x555555583424 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/utf32_be.c/utf32be_mbc_case_fold/onigenc_unicode_mbc_case_fold/onigenc_unicode_mbc_case_fold+0x2f424) (BuildId: 8318bc5e19ca5cdfa35b1ae51b78d079d6ab6a54)

0x7c1ff6c20012 is located 0 bytes after 2-byte region [0x7c1ff6c20010,0x7c1ff6c20012)
allocated by thread T0 here:
    #0 0x555555626414 in malloc (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/utf32_be.c/utf32be_mbc_case_fold/onigenc_unicode_mbc_case_fold/onigenc_unicode_mbc_case_fold+0xd2414) (BuildId: 8318bc5e19ca5cdfa35b1ae51b78d079d6ab6a54)
    #1 0x55555566c069 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/utf32_be.c/utf32be_mbc_case_fold/onigenc_unicode_mbc_case_fold.c:24:30
    #2 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/ambrose/vsproject/TestLib/oniguruma/src/utf32_be.c:72:65 in utf32be_mbc_to_code
Shadow bytes around the buggy address:
  0x7c1ff6c1fd80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1fe00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1fe80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1ff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1ff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7c1ff6c20000: fa fa[02]fa fa fa fa fa fa fa fa fa fa fa fa fa
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
==1313179==ABORTING
[Inferior 1 (process 1313179) exited with code 01]
```
