# Bit-Level Integer Coding Rules

In several of the following problems, we will artificially restrict what programming constructs you can use to help you gain a better understanding of the bit-level, logic, and arithmetic operations of C. In answering these problems, your code must follow these rules:

* Assumption
  * Integers are represented in two's-complement form.
  * Right shifts of signed data are performed arithmetically.
  * Data type int is w byts long. For some of the problems, you will be given a specific value for w, but otherwise your code should work as long as w is a multiple of 8. You can use the expression `sizeof(int)<<3` to compute w.
* Forbidden
  * Conditionals(`if` or `?:`), loops, switch statements, function calls, and macro invocations.
  * Division, modulus, and multiplication.
  * Relative comparison operators(`<`,`>`,`<=`, and `>=`).
* Allowed operations
  * All bit-level and logic operations.
  * Left and right shifts, but only when with shift amount between 0 and w - 1.
  * Addition and subtraction.
  * Equality (`==`) and inequality (`!=`) tests. (Some of the problem do not allow these.)
  * Integer constants `INT_MIN` and `INT_MAX`.
  * Casting between data types `int` and `unsigned`, either explicitly or implicitly.

Even with these rules, you should try to make your code readable by choosing descriptive variable names and using comments to describe the logic behind your solutions. As an example, the following code extracts the most significant byte from integer argument x:

```c
/* Get most significant byte from x */
int get_msb(int x) {
    /* Shift by w-8 */
    int shift_val = (sizeof(int)-1)<<3;
    /* Arithmetic shift */
    int xright = x >> shift_val;
    /* Zero all but LSB */
    return xright & 0xFF;
}
```

# Bit-Level Floating-Point Coding Rules

In the following problems, you will write code to implement floating-point functions, operating directly on bit-level representations of floating-point numbers. Your code should exactly replicate the conventions for IEEE floating-point operations, including using round-to-even mode when rounding is required.
To this end, we define data type float_bits to be equivalent to unsigned:

```c
/* Access bit-level representation floating-point number */
typedef unsigned float_bits;
```

Rather than using data type float in your code, you will use float_bits. You may use both int and unsigned data types, including unsigned and integer constants and operations. You may not use any unions, structs, or arrays. Most significantly, you may not use any floating-point data types, operations, or constants. Instead, your code should perform the bit manipulations that implement the specified floating-point operations.
The following function illustrates the use of these coding rules. For argument f, it returns +-0 if f is denormalized (perserving the sign of f), and returns f otherwise.

```c
/* If f is denorm, return 0.  Otherwise, return f */
float_bits float_denorm_zero(float_bits f) {
    /* Decompose bit representation into parts */
    unsigned sign = f >> 31;
    unsigned exp =  f >> 23 & 0xFF;
    unsigned frac = f       & 0x7FFFFF;
    if (exp == 0) {
        /* Denormalized.    Set fraction to 0 */
        frac = 0;
    }
    /* Reassemble bits */
    return (sign << 31) | (exp << 23) | frac;
}
```
