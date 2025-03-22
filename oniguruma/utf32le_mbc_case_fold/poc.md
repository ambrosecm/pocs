## Desctiption
When using the utf32le_mbc_case_fold function to handle a specific input, AddressSanitizer: heap-buffer-overflow in utf32le_mbc_case_fold /oniguruma/src/utf32_le.c:100
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/utf32_le.c#L94-L100
## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/utf32le_mbc_case_fold/utf32le_mbc_case_fold.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/utf32le_mbc_case_fold/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/utf32le_mbc_case_fold/utf32le_mbc_case_fold) and run the following cmd:
```
 $ ./utf32le_mbc_case_fold ./poc
```

## Detail
### ASAN report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/utf32_le.c/generate/utf32le_mbc_case_fold/utf32le_mbc_case_fold output/default/crashes/id:000000,sig:06,src:000000,time:2578,execs:649,op:havoc,rep:4
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==3261357==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x7c1ff6c20011 at pc 0x55555566ade5 bp 0x7fffffffd780 sp 0x7fffffffd778
READ of size 1 at 0x7c1ff6c20011 thread T0
[Detaching after fork from child process 3269311]
    #0 0x55555566ade4 in utf32le_mbc_case_fold /home/ambrose/vsproject/TestLib/oniguruma/src/utf32_le.c:100:36
    #1 0x55555566c27f in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/utf32_le.c/generate/utf32le_mbc_case_fold.c:41:18
    #2 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #3 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #4 0x555555583424 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/utf32_le.c/generate/utf32le_mbc_case_fold/utf32le_mbc_case_fold+0x2f424) (BuildId: a9da4e880f1bbe5e6690f40da7294c4f8469bb17)

0x7c1ff6c20011 is located 0 bytes after 1-byte region [0x7c1ff6c20010,0x7c1ff6c20011)
allocated by thread T0 here:
    #0 0x555555626414 in malloc (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/utf32_le.c/generate/utf32le_mbc_case_fold/utf32le_mbc_case_fold+0xd2414) (BuildId: a9da4e880f1bbe5e6690f40da7294c4f8469bb17)
    #1 0x55555566bfb9 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/utf32_le.c/generate/utf32le_mbc_case_fold.c:24:33
    #2 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/ambrose/vsproject/TestLib/oniguruma/src/utf32_le.c:100:36 in utf32le_mbc_case_fold
Shadow bytes around the buggy address:
  0x7c1ff6c1fd80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1fe00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1fe80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1ff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7c1ff6c1ff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7c1ff6c20000: fa fa[01]fa fa fa fa fa fa fa fa fa fa fa fa fa
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
==3261357==ABORTING
[Inferior 1 (process 3261357) exited with code 01]
```
