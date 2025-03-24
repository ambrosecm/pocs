## Desctiption
When using the tdefl_record_literal function to handle a specific input. Program received signal SIGSEGV, Segmentation fault. in tdefl_record_literal at /LuPng/miniz.h:3033

https://github.com/jansol/LuPng/blob/5ec546e0d16d0fb9316967949b2676227eb93736/miniz.h#L3030-L3033

## Test Environment
Ubuntu 22.04.1, 64bit
LuPng(commits on Aug 28, 2021 master https://github.com/jansol/LuPng/commit/5ec546e0d16d0fb9316967949b2676227eb93736)
[program source file](https://github.com/ambrosecm/pocs/blob/main/LuPng/tdefl_record_literal/tdefl_record_literal.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/LuPng/tdefl_record_literal/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/LuPng/tdefl_record_literal/tdefl_record_literal) and run the following cmd:
```
 $ ./tdefl_record_literal ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/crashes/miniz.h/generate/tdefl_record_literal/tdefl_record_literal output/default/crashes/id:000000,sig:11,src:000000,time:122,execs:59,op:havoc,rep:12
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x0000555555780ce2 in tdefl_record_literal (d=0x7ffff7bb1800, lit=2 '\002') at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:3033
3033        *d->m_pLZ_code_buf++ = lit;
(gdb) bt
#0  0x0000555555780ce2 in tdefl_record_literal (d=0x7ffff7bb1800, lit=2 '\002')
    at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:3033
#1  main (argc=2, argv=0x7fffffffda98)
    at output/LuPng_deepseek24/harness/code/miniz.h/generate/tdefl_record_literal.c:38
(gdb) p d->m_pLZ_code_buf
$1 = (mz_uint8 *) 0xbebebebebebebebf <error: Cannot access memory at address 0xbebebebebebebebf>
```
