

.text
.global _start
_start:



ldr sp,=4096            //nandÆô¶¯
bl main

halt:
    b halt
























