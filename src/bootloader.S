.section .text
.global _start

_start:
    ldr sp, =_stack_top  @ Ustawienie wskaźnika stosu
    bl main              @ Skok do funkcji main
    b .                  @ Pętla nieskończona (fallback)
