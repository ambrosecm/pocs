## Desctiption
When using the mz_zip_validate_archive function to handle a specific input. Program received signal SIGILL, Illegal instruction. in mz_zip_validate_archive at /LuPng/miniz.h:6768

https://github.com/jansol/LuPng/blob/5ec546e0d16d0fb9316967949b2676227eb93736/miniz.h#L6757-L6768

## Test Environment
Ubuntu 22.04.1, 64bit
LuPng(commits on Aug 28, 2021 master https://github.com/jansol/LuPng/commit/5ec546e0d16d0fb9316967949b2676227eb93736)
[program source file](https://github.com/ambrosecm/pocs/blob/main/LuPng/mz_zip_validate_archive/mz_zip_validate_archive.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/LuPng/mz_zip_validate_archive/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/LuPng/mz_zip_validate_archive/mz_zip_validate_archive) and run the following cmd:
```
 $ ./mz_zip_validate_archive ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/crashes/miniz.h/generate/mz_zip_validate_archive/mz_zip_validate_archive output/default/crashes/id:000000,sig:04,src:000000,time:811,execs:162,op:quick,pos:104
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x00005555557184d0 in mz_zip_validate_archive (pZip=0x7caff6e20040, flags=112) at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:6768
6768        if (!pState->m_zip64)
(gdb) bt
#0  0x00005555557184d0 in mz_zip_validate_archive (pZip=0x7caff6e20040, flags=112)
    at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:6768
#1  0x000055555577f93c in main (argc=2, argv=0x7fffffffda88)
    at output/LuPng_deepseek24/harness/code/miniz.h/generate/mz_zip_validate_archive.c:48
(gdb) p pState->m_zip64
Cannot access memory at address 0x83
```
