
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
