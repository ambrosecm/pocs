## Desctiption
When using the onig_regset_free function to handle a specific input, Program received signal SIGSEGV, Segmentation fault. onig_regset_free at /oniguruma/src/regexec.c:6126

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regexec.c#L6115-L6126

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
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regexec.c/generate/onig_regset_new/onig_regset_new output/default/crashes/id:000000,sig:11,src:000003,time:72,execs:32,op:quick,pos:1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x0000555555587fd7 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) ()
(gdb) bt
#0  0x0000555555587fd7 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) ()
#1  0x000055555562827c in __interceptor_free ()
#2  0x00007ffff7f2e32c in onig_free_body () from /lib/x86_64-linux-gnu/libonig.so.5
#3  0x00007ffff7f2e482 in onig_free () from /lib/x86_64-linux-gnu/libonig.so.5
#4  0x00005555556fb14d in onig_regset_free (set=0x7c3ff6a20050)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regexec.c:6126
#5  0x0000555555706ab3 in main (argc=2, argv=0x7fffffffdac8)
    at output/oniguruma_deepseek24/harness/code/regexec.c/generate/onig_regset_new.c:77
```
