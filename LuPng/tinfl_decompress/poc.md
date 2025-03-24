## Desctiption
When using the tinfl_decompress function to handle a specific input. Program received signal SIGILL, Illegal instruction. in tinfl_decompress at /LuPng/miniz.h:3986

https://github.com/jansol/LuPng/blob/5ec546e0d16d0fb9316967949b2676227eb93736/miniz.h#L3986

## Test Environment
Ubuntu 22.04.1, 64bit
LuPng(commits on Aug 28, 2021 master https://github.com/jansol/LuPng/commit/5ec546e0d16d0fb9316967949b2676227eb93736)
[program source file](https://github.com/ambrosecm/pocs/blob/main/LuPng/tinfl_decompress/tinfl_decompress_mem_to_heap.c)

## How to trigger
Download the [poc file](https://github.com/ambrosecm/pocs/blob/main/LuPng/tinfl_decompress/poc) , [program](https://github.com/ambrosecm/pocs/blob/main/LuPng/tinfl_decompress/tinfl_decompress_mem_to_heap) and run the following cmd:
```
 $ ./tinfl_decompress_mem_to_heap ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/LuPng_deepseek24/crashes/miniz.h/generate/tinfl_decompress_mem_to_heap/tinfl_decompress_mem_to_heap output/default/crashes/id:000000,sig:04,src:000001,time:247,execs:94,op:havoc,rep:14
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGILL, Illegal instruction.
0x000055555569197e in tinfl_decompress (r=0x7bfff6009020, pIn_buf_next=0x7c2ff6c20042 "\325\361\277\026\246\343\n\352x\373\372\036-\026\251g\300 ", pIn_buf_size=0x7bfff600bc20, pOut_buf_start=0x7cbff6c20040 "\037", '\276' <repeats 127 times>, pOut_buf_next=0x7cbff6c20040 "\037", '\276' <repeats 127 times>, pOut_buf_size=0x7bfff600bc40, decomp_flags=4) at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:3986
3986                                bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE32(pIn_buf_cur)) << num_bits);
(gdb) bt
#0  0x000055555569197e in tinfl_decompress (r=0x7bfff6009020, 
    pIn_buf_next=0x7c2ff6c20042 "\325\361\277\026\246\343\n\352x\373\372\036-\026\251g\300 ", 
    pIn_buf_size=0x7bfff600bc20, pOut_buf_start=0x7cbff6c20040 "\037", '\276' <repeats 127 times>, 
    pOut_buf_next=0x7cbff6c20040 "\037", '\276' <repeats 127 times>, pOut_buf_size=0x7bfff600bc40, 
    decomp_flags=4) at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:3986
#1  0x00005555556cadd7 in tinfl_decompress_mem_to_heap (pSrc_buf=0x7c2ff6c20040, src_buf_len=20, 
    pOut_len=0x7bfff5809020, flags=0) at /home/ambrose/vsproject/TestLib/LuPng/miniz.h:4225
#2  0x0000555555780a39 in main (argc=2, argv=0x7fffffffda78)
    at output/LuPng_deepseek24/harness/code/miniz.h/generate/tinfl_decompress_mem_to_heap.c:45
```
