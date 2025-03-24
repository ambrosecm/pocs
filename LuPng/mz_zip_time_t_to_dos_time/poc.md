## Desctiption
When using the mz_zip_time_t_to_dos_time function to handle a specific input. Program received signal SIGILL, Illegal instruction. in mz_zip_time_t_to_dos_time at /LuPng/miniz.h:4700

https://github.com/jansol/LuPng/blob/5ec546e0d16d0fb9316967949b2676227eb93736/miniz.h#L4682-L4700

## Test Environment
Ubuntu 22.04.1, 64bit
LuPng(commits on Aug 28, 2021 master https://github.com/jansol/LuPng/commit/5ec546e0d16d0fb9316967949b2676227eb93736)
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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/crashes/miniz.h/generate/mz_zip_time_t_to_dos_time/mz_zip_time_t_to_dos_time output/default/crashes/id:000000,sig:04,src:000000,time:144,execs:43,op:flip1,pos:0
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x00005555557358d4 in mz_zip_time_t_to_dos_time (time=-1577058278, pDOS_time=0x7bfff5c09080, pDOS_date=0x7bfff5c09090) at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:4700
4700        *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
(gdb) bt
#0  0x00005555557358d4 in mz_zip_time_t_to_dos_time (time=-1577058278, pDOS_time=0x7bfff5c09080, 
    pDOS_date=0x7bfff5c09090) at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:4700
#1  0x00005555557809ff in main (argc=2, argv=0x7fffffffda88)
    at output/LuPng_deepseek24/harness/code/miniz.h/generate/mz_zip_time_t_to_dos_time.c:35
(gdb) p *tm
$1 = {tm_sec = 22, tm_min = 15, tm_hour = 8, tm_mday = 11, tm_mon = 0, tm_year = 20, tm_wday = 0, tm_yday = 10, 
  tm_isdst = 0, tm_gmtoff = 28800, tm_zone = 0x7c2ff6e200b0 "CST"}
```
