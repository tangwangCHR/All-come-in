

.text
.global _start
_start:



ldr sp,=4096            //nand����
bl main

halt:
    b halt
























