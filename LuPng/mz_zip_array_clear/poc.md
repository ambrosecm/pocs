## Desctiption
When using the mz_zip_array_clear function to handle a specific input. Program received signal SIGSEGV, Segmentation fault. in mz_zip_array_clear at /LuPng/miniz.h:4607
https://github.com/jansol/LuPng/blob/5ec546e0d16d0fb9316967949b2676227eb93736/miniz.h#L4605-L4607

## Test Environment
Ubuntu 22.04.1, 64bit
LuPng(commits on Aug 28, 2021 master https://github.com/jansol/LuPng/commit/5ec546e0d16d0fb9316967949b2676227eb93736)
[program source file](https://github.com/ambrosecm/pocs/blob/main/LuPng/mz_zip_array_clear/mz_zip_writer_end.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/LuPng/mz_zip_array_clear/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/LuPng/mz_zip_array_clear/mz_zip_writer_end) and run the following cmd:
```
 $ ./mz_zip_writer_end ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/crashes/miniz.h/generate/mz_zip_writer_end/mz_zip_writer_end output/default/crashes/id:000000,sig:11,src:000000,time:16323,execs:6994,op:havoc,rep:41
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x00005555557202bb in mz_zip_array_clear (pZip=0x7bfff5c09020, pArray=0x710000000000) at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:4607
4607        pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
(gdb) bt
#0  0x00005555557202bb in mz_zip_array_clear (pZip=0x7bfff5c09020, pArray=0x710000000000)
    at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:4607
#1  mz_zip_writer_end_internal (pZip=0x7bfff5c09020, set_last_error=1)
    at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:6972
#2  0x0000555555723ee2 in mz_zip_writer_end (pZip=0x7bfff5c09020)
    at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:8712
#3  0x000055555577f98f in main (argc=2, argv=0x7fffffffdaa8)
    at output/LuPng_deepseek24/harness/code/miniz.h/generate/mz_zip_writer_end.c:37
(gdb) p pZip->m_pAlloc_opaque
$1 = (void *) 0x0
(gdb) p pArray->m_p
Cannot access memory at address 0x710000000000
```
