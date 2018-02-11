# ***
# Modify the code you wrote for Problem 4.47 to implement the test and swap in
# the bubblesort function (lines 6-11) using no jumps and at most three
# conditional moves.

bubble:
    irmovq  $8, %r8
begin:
    rrmovq  %rsi, %rax
    xorq    %rdi, %rax
    je      sorted
    subq    %r8, %rsi
    rrmovq  %rdi, %rcx
    rrmovq  %rdi, %rdx
round:
    rrmovq  %rcx, %rax
    xorq    %rsi, %rax
    je      begin
    addq    %r8, %rdx
    mrmovq  (%rcx), %r10
    mrmovq  (%rdx), %r11
    rrmovq  %r10, %rax
# Compare and swap two numbers
    subq    %r11, %rax
    cmovg   %r10, %rax
    cmovg   %r11, %r10
    cmovg   %rax, %r11
    rmmovq  %r10, (%rcx)
    rmmovq  %r11, (%rdx)
    addq    %r8, %rcx
    jmp     round
sorted:
    ret
