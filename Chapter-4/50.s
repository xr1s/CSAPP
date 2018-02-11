# ***
# In Section 3.6.8, we saw that a common way to implement switch statements is
# to create a set of code blocks and then index those blocks using a jump table.
# Consider the C code shown in Figure 4.69 for a function switchv, along with
# associated test code.
#
# #include <stdio.h>
# /* Example use of switch statement */
#
# long switchv(long idx) {
#     long result = 0;
#     switch(idx) {
#     case 0:
#         result = 0xaaa;
#         break;
#     case 2:
#     case 5:
#         result = 0xbbb;
#         break;
#     case 3:
#         result = 0xccc;
#         break;
#     default:
#         result = 0xddd;
#     }
#     return result;
# }
#
# /* Testing Code */
# #define CNT 8
# #define MINVAL -1
#
# int main() {
#     long vals[CNT];
#     long i;
#     for (i = 0; i < CNT; i++) {
#         vals[i] = switchv[i + MINVAL);
#         printf("idx = %ld, val = 0x%lx\", i + MINVAL, vals[i]);
#     }
#     return 0;
# }
#
# Figure 4.69  Switch statements can be translated into Y86-64 code. This
# requires implementation of a jump table.
#
#     Implement switchv in Y86-64 using a jump table. Although the Y86-64
# instruction set does not include an indirect jump instruction, you can get the
# same effect by pushing a computed address onto the stack and then executing
# the ret instruction. Implement test code similar to what is shown in C to
# demonstrate that your implementation of switchv will handle both the cases
# explicitly as well as those that trigger the default case.

.global switchv

switchv:
    irmovq  $5, %rsi
    subq    %rdi, %rsi
    jbe     other
    leaq    jt(%rip), %rdx
    mrmovq  (%rdx,%rdi,8), %rax
    addq    %rdx, %rax
    pushq   %rax
    retq
case0:
    irmovq  $0xaaa, %rax
    jmp     return
case2:
case5:
    irmovq  $0xbbb, %rax
    jmp     return
case3:
    irmovq  $0xccc, %rax
    jmp     return
other:
    irmovq  $0xddd, %rax
return:
    rep ret
jt:
    .quad case0-jt
    .quad other-jt
    .quad case2-jt
    .quad case3-jt
    .quad other-jt
    .quad case5-jt
