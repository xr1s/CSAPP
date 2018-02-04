# Write a function in assembly code that matches the behavior of the function
# find_range in Figure 3.51. Your code should contain only one floating-point
# comparison instruction, and then it should use conditional moves to generate
# the correct result. You might want to make use of the instruction cmovp (move
# if even parity). Test your code on all 2^32 possible argument values. Web
# Aside ASM:EASM on page 178 describes how to incorporate functions written in
# assembly code into C programs.

.global find_range

find_range:
    vxorps      %xmm1, %xmm1, %xmm1
    vucomiss    %xmm1, %xmm0
    setz        %al
    setb        %cl
    movzbq      %cl, %rcx
    movzbq      %al, %rax
    leaq        -3(%rax,%rcx,2), %rax
    notq        %rax
    movq        $3, %rcx
    cmovp       %rcx, %rax
    retq
