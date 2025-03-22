## Desctiption
When using the node_free_body function to handle a specific input, Program received signal SIGSEGV, Segmentation fault. in node_free_body at /oniguruma/src/regparse.c:2196

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regparse.c#L2187-L2196

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regparse.c/generate/node_free_body/node_free_body output/default/crashes/id:000000,sig:11,src:000003,time:2418,execs:635,op:havoc,rep:16
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x0000555555587f77 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) ()
(gdb) bt
#0  0x0000555555587f77 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) ()
#1  0x000055555562821c in __interceptor_free ()
#2  0x000055555567dcde in node_free_body (node=0x7c6ff6c20020)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:2196
#3  0x0000555555699eda in main (argc=2, argv=0x7fffffffdac8)
    at output/oniguruma_deepseek24/harness/code/regparse.c/generate/node_free_body.c:40
```
