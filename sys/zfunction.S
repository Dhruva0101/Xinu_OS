/* zfunction.S - _zfunction */

  .text
  .globl zfunction
zfunction:

push %ebp
mov  %esp,%ebp
mov  0x8(%ebp),%eax
and  $0xfffff00f, %eax
shl  $0x8, %eax
or   $0xff, %eax
pop  %ebp
ret

