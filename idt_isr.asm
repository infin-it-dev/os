section .data
idt:
    times 256 dd 0, 0

section .text
global load_idt
load_idt:
    lidt [idt_descriptor]
    ret

idt_descriptor:
    dw idt_end - idt - 1
    dd idt

idt_end:
