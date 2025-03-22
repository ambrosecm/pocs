## Desctiption
When using the onig_node_free function to handle a specific input, AddressSanitizer: attempting free on address which was not malloc()-ed in onig_node_free /oniguruma/src/regparse.c:2268
https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regparse.c#L2258-L2268

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/node_drop_group/node_drop_group output/default/crashes/id:000000,sig:06,src:000001,time:3492,execs:953,op:havoc,rep:15
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
=================================================================
==4012501==ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed: 0x7bfff5809020 in thread T0
[Detaching after fork from child process 4021243]
    #0 0x5555556281b6 in free (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/node_drop_group/node_drop_group+0xd41b6) (BuildId: 95ed5bab4229693b38bb25a3e96ea3e2d56729fc)
    #1 0x55555567d18e in onig_node_free /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:2268:3
    #2 0x55555569a37a in node_drop_group /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:2744:3
    #3 0x555555699f4e in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regparse.c/generate/node_drop_group.c:38:5
    #4 0x7ffff7a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #5 0x7ffff7a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #6 0x555555585464 in _start (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/node_drop_group/node_drop_group+0x31464) (BuildId: 95ed5bab4229693b38bb25a3e96ea3e2d56729fc)

Address 0x7bfff5809020 is located in stack of thread T0 at offset 32 in frame
    #0 0x555555699967 in main /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/harness/code/regparse.c/generate/node_drop_group.c:12

  This frame has 1 object(s):
    [32, 104) 'node' (line 27) <== Memory access at offset 32 is inside this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: bad-free (/home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/node_drop_group/node_drop_group+0xd41b6) (BuildId: 95ed5bab4229693b38bb25a3e96ea3e2d56729fc) in free
==4012501==ABORTING
[Inferior 1 (process 4012501) exited with code 01]
```
