## Desctiption
When using the tdefl_optimize_huffman_table function to handle a specific input. Program received signal SIGILL, Illegal instruction. in tdefl_optimize_huffman_table at /LuPng/miniz.h:2256

https://github.com/jansol/LuPng/blob/5ec546e0d16d0fb9316967949b2676227eb93736/miniz.h#L2256

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
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/crashes/miniz.h/generate/tdefl_optimize_huffman_table/tdefl_optimize_huffman_table output/default/crashes/id:000000,sig:04,src:000002,time:605472,execs:177866,op:havoc,rep:61
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x0000555555782aa2 in tdefl_optimize_huffman_table (d=0x7ffffffaf880, table_num=0, table_len=511, code_size_limit=15, static_table=0) at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:2256
2256            if ((code_size = d->m_huff_code_sizes[table_num][i]) == 0)
(gdb) bt
#0  0x0000555555782aa2 in tdefl_optimize_huffman_table (d=0x7ffffffaf880, table_num=0, table_len=511, 
    code_size_limit=15, static_table=0) at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:2256
#1  0x000055555577fcf9 in main (argc=2, argv=0x7fffffffda68)
    at output/LuPng_deepseek24/harness/code/miniz.h/generate/tdefl_optimize_huffman_table.c:59
```
