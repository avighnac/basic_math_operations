# basic_math_operations
A biginteger library for Linux written in assembly and C.

Have you ever wanted to add, subtract, or multiply huge numbers but your calculator or favourite programming language only gives you an approximation?

For example, let's say you wanted to, for some reason, multiply `387261987198787123479468764398` by `1897346897629873468761342`. These numbers are extremely huge, and would be a programmatic nightmare to deal with. Well, that is, without this library.

Here's how simple it becomes with basic_math_operations.

```c
#include "basic_math_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char a[] = "387261987198787123479468764398";
  char b[] = "1897346897629873468761342";
  
  char *res = (char *)calloc(strlen(a) + strlen(b) + 1);
  multiply(a, b, res);
  
  printf("%s * %s = %s\n", a, b, res);
  
  free(res);
}
```

And that too with blazing fast speeds! Most of the heavy-lifting of these algorithms is written in x86 assembly in order to maximize its efficiency.

Downloading and using this library is as simple as including the header file (`basic_math_operations.h`), and linking the `libbasic_math_operations.a` file using `-L. -lbasic_math_operations`. Of course, it works with both C and C++, but is primarily _meant_ to be a C library (you'd have to use C-styled strings even in C++).

# Compilation
Here's a full example of compiling a program made with `basic_math_operations`.
# C
main.c:
```c
#include "basic_math_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char* a = (char *)calloc(1024, 1);
  char* b = (char *)calloc(1024, 1);
  char* res = (char *)calloc(1100, 1);
  printf("Enter the first number: ");
  scanf("%s", a);
  printf("Enter the second number: ");
  scanf("%s", b);

  divide(a, b, res, 40);

  printf("%s / %s = %s\n", a, b, res);

  free(a);
  free(b);
  free(res);
}
```

Compile this with `gcc main.c -L. -lbasic_math_operations -o filename.out`. Make sure `basic_math_operations.h` and `libbasic_math_operations.a` are in the same directory as `main.c`.

# Features
This library has functions that can add, subtract, multiply, and divide with arbitrary precision.

This is *important*. When allocating memory for the result buffer, **use `calloc()` and not `malloc()`** (for `calloc`, you can use malloc syntax, just add `1` as it's second argument). Some functions may malfunction and result in **undefined behaviour** if you use `malloc()` instead of `calloc()`.

I don't know if this needs to be said, but the functions higher up in each of their respective sections are *usually* faster than their lower counterparts. If you know that two numbers will have the same length, using the specialized function will be faster.

Detailed information for each of these functions can be found in the `basic_math_operations.h` file. This is just a brief.

Addition:
- `add_whole_same_length(...)` adds two non-negative integers of the same length.
- `add_whole(...)` adds two non-negative integers.
- `addp(...)` adds two non-negative rational numbers.
- `add(...)` adds two rational numbers.

Subtraction:
All subtract functions can return a negative number, but only some can take negative numbers as input. All of them also subtract the second argument from the first argument.
- `subtract_whole_same_length(...)` subtracts two non-negative integers of the same length.
- `subtract_whole(...)` subtracts two non-negative integers.
- `subtractp(...)` subtracts two non-negative rational numbers.
- `subtract(...)` subtracts two rational numbers.

Multiplication:
- `multiply_whole(...)` multiplies two non-negative integers.
- `multiplyp(...)` multiplies two non-negative rational numbers.
- `multiply(...)` multiplies two rational numbers.

Division:
- `divide_whole_with_remainder(...)` performs modular division on the input.
- `divide_whole()` divides two non-negative integers.
- `dividep()` divides two non-negative rational numbers.
- `divide()` divides two rational numbers.