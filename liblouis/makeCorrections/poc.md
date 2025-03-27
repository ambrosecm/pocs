I'm constructing fuzz drivers for liblouis.

## Desctiption
When I used the makeCorrections function to handle a specific input. Program received signal SIGSEGV, Segmentation fault. in makeCorrections at /liblouis/lou_translateString.c:301

https://github.com/liblouis/liblouis/blob/2682d54c79333f9d7c06a8080ac5acb17a62d6fa/liblouis/lou_translateString.c#L253-L301

The primary cause is that the parameter in makeCorrections is corrupted and not be checked. It points to an inaccessible address, leading to a segmentation fault.


## Test Environment
Ubuntu 22.04.1, 64bit
Liblouis (v3.33.0 master https://github.com/liblouis/liblouis/commit/2682d54c79333f9d7c06a8080ac5acb17a62d6fa)
[program source code file]()

## How to trigger
Download the [poc file]() , [program]() and run the following cmd:
```
 $ ./ ./poc
```

## Detail
### GDB report
```
(gdb) r
Starting program: /home/ambrose/vsproject/HIMFuzz/harness/output/liblouis_deepseek24/crashes/lou_translateString.c/_lou_translate/makeCorrections/makeCorrections output/default/crashes/id:000000,sig:11,src:000002,time:81482,execs:2785,op:havoc,rep:1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x0000555555674a63 in makeCorrections (table=0x7ffff7568800, input=0x7bfff600a160, output=0x7bfff600a1a0, posMapping=0x7bfff600a1e0, typebuf=0x7bfff600b260, realInlen=0x7bfff600bb00, cursorPosition=0x7bfff600bae0, cursorStatus=0x7bfff600baf0, mode=0) at /home/ambrose/vsproject/TestLib/liblouis/liblouis/lou_translateString.c:301
301                                             transOpcode = transRule->opcode;
(gdb) bt
#0  0x0000555555674a63 in makeCorrections (table=0x7ffff7568800, input=0x7bfff600a160, output=0x7bfff600a1a0, 
    posMapping=0x7bfff600a1e0, typebuf=0x7bfff600b260, realInlen=0x7bfff600bb00, cursorPosition=0x7bfff600bae0, 
    cursorStatus=0x7bfff600baf0, mode=0) at /home/ambrose/vsproject/TestLib/liblouis/liblouis/lou_translateString.c:301
#1  0x0000555555692c2a in main (argc=2, argv=0x7fffffffda68)
    at output/liblouis_deepseek24/harness/code/lou_translateString.c/_lou_translate/makeCorrections.c:55
(gdb) p transRule->opcode
Cannot access memory at address 0x8007ad670dac
```
