## Desctiption
When using the stack_double function to handle a specific input, AddressSanitizer: stack-buffer-overflow in stack_double /oniguruma/src/regexec.c:1744

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regexec.c#L1728-L1744

## Test Environment
Ubuntu 22.04.1, 64bit
oniguruma(v6.9.10 master https://github.com/kkos/oniguruma/commit/05bb130c9ad54877e73d1caf08dd95e6ff199d99)
[program source file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/stack_double/stack_double.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/oniguruma/stack_double/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/oniguruma/stack_double/stack_double) and run the following cmd:
```
 $ ./stack_double ./poc
```

## Detail
### ASAN report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regexec.c/generate/stack_double/stack_double output/default/crashes/id:000000,sig:06,src:000000,time:3519435,execs:979602,op:havoc,rep:15
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==1654115==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7bfff5a090a0 at pc 0x555555706369 bp 0x7fffffffd480 sp 0x7fffffffd478
READ of size 8 at 0x7bfff5a090a0 thread T0
[Detaching after fork from child process 1662841]
    #0 0x555555706368 in stack_double /home/ambrose/vsproject/TestLib/oniguruma/src/regexec.c:1744:14
    #1 0x555555706020 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regexec.c/generate/stack_double.c:38:18
    #2 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #3 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #4 0x5555555854b4 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regexec.c/generate/stack_double/stack_double+0x314b4) (BuildId: ebfd70e45579bd69b892029f263724795fdcf407)

Address 0x7bfff5a090a0 is located in stack of thread T0 at offset 160 in frame
    #0 0x555555705957 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regexec.c/generate/stack_double.c:6

  This frame has 6 object(s):
    [32, 40) 'alloc_base' (line 20)
    [64, 72) 'stk_base' (line 21)
    [96, 104) 'stk_end' (line 22)
    [128, 136) 'stk' (line 23)
    [160, 164) 'is_alloca' (line 24) <== Memory access at offset 160 partially overflows this variable
    [176, 184) 'msa' (line 25)
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/ambrose/vsproject/TestLib/oniguruma/src/regexec.c:1744:14 in stack_double
Shadow bytes around the buggy address:
  0x7bfff5a08e00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5a08e80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5a08f00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5a08f80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5a09000: f1 f1 f1 f1 00 f2 f2 f2 00 f2 f2 f2 00 f2 f2 f2
=>0x7bfff5a09080: 00 f2 f2 f2[04]f2 00 f3 f3 f3 f3 f3 00 00 00 00
  0x7bfff5a09100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5a09180: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5a09200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5a09280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7bfff5a09300: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==1654115==ABORTING
[Inferior 1 (process 1654115) exited with code 01]
```
