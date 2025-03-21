## Desctiption
When using the onig_strcpy function to handle a specific input, Program received signal SIGSEGV, Segmentation fault. in onig_strcpy at /oniguruma/src/regparse.c:479

https://github.com/kkos/oniguruma/blob/c197d53ec6a25d7b068809130f046c006650d1a5/src/regparse.c#L474-L479

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/oniguruma_deepseek24/crashes/regcomp.c/unravel_case_fold_string/unravel_cf_string_add/unravel_cf_string_add output/default/crashes/id:000000,sig:11,src:000002,time:580811,execs:201720,op:havoc,rep:2
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
memcpy () at ../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:222
222     ../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S: No such file or directory.
(gdb) bt
#0  memcpy () at ../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:222
#1  0x0000555555625eec in __asan_memcpy ()
#2  0x000055555578df5c in onig_strcpy (dest=0x7ccff6c20040 '\276' <repeats 137 times>, 
    src=0x8 <error: Cannot access memory at address 0x8>, 
    end=0x80 <error: Cannot access memory at address 0x80>)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:479
#3  0x00005555557a95c3 in strcat_capa_from_static (dest=0x7c6ff6c20044 "", dest_end=0x7c6ff6c20044 "", 
    src=0x8 <error: Cannot access memory at address 0x8>, 
    src_end=0x80 <error: Cannot access memory at address 0x80>, capa=136)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:539
#4  0x00005555557a83e5 in onig_node_str_cat (node=0x7c6ff6c20020, 
    s=0x8 <error: Cannot access memory at address 0x8>, end=0x80 <error: Cannot access memory at address 0x80>)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:3398
#5  0x00005555557bd87e in node_set_str (node=0x7c6ff6c20020, 
    s=0x8 <error: Cannot access memory at address 0x8>, end=0x80 <error: Cannot access memory at address 0x80>)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:3487
#6  0x00005555557aabcd in node_new_str (s=0x8 <error: Cannot access memory at address 0x8>, 
    end=0x80 <error: Cannot access memory at address 0x80>)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:3498
#7  0x00005555557aab15 in onig_node_new_str (s=0x8 <error: Cannot access memory at address 0x8>, 
    end=0x80 <error: Cannot access memory at address 0x80>)
    at /home/ambrose/vsproject/TestLib/oniguruma/src/regparse.c:3523
#8  0x0000555555691896 in unravel_cf_string_add (rlist=0x7bfff5a09070, rsn=0x7bfff5a09090, 
    s=0x8 <error: Cannot access memory at address 0x8>, 
    end=0x80 <error: Cannot access memory at address 0x80>, flag=6)
```
