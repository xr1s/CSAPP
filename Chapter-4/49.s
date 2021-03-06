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
# Compare and swap two numbers
    rrmov   %r10, %r9
    xorq    %r11, %r9
    subq    %r11, %rax
    irmovq  $0, %rax
    rrmovq  %r10, %rax
    cmovg   %r9, %rax
    xorq    %r9, %r10
    xorq    %r9, %r11
    xorq    %rax, %r10
    xorq    %rax, %r11
    rmmovq  %r10, (%rdx)
    rmmovq  %r11, (%rcx)
    addq    %r8, %rcx
    jmp     round
sorted:
    ret
