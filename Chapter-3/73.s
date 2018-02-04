# Write a function in assembly code that matches the behavior of the function
# find_range in Figure 3.51. Your code should contain only one floating-point
# comparison instruction, and then it should use conditional branches to
# generate the correct result. Test your code on 2^32 possible argument values.
# Web Aside ASM:EASM on page 178 describes how to incorporate functions written
# in assembly code into C programs.

.global find_range

find_range:
    vxorps      %xmm1, %xmm1, %xmm1
    vucomiss    %xmm1, %xmm0
    jp          nan
    jb          neg
    jz          zero
    movq        $2, %rax
    retq
nan:
    movq        $3, %rax
    retq
neg:
    xorq        %rax, %rax
    retq
zero:
    movq        $1, %rax
    retq
