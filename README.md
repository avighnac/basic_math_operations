# basic_math_operations
A biginteger library for Linux written in assembly and C.

Have you wanted to add, subtract, or multiply huge numbers but your calculator or favourite programming language only gives you an approximation?

For example, let's say you wanted to, for some reason, multiply `387261987198787123479468764398` by `1897346897629873468761342`. These numbers are extremely huge, and would be a programmatic nightmare to deal with. Well, that is, without this library.

Here's how simple it becomes with basic_math_operations.

```c
#include <basic_math_operations.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char a[] = "387261987198787123479468764398";
  char b[] = "1897346897629873468761342";
  
  char *res = (char *)calloc(strlen(a) + strlen(b) + 1);
  multiply(a, b, res);
  
  printf("%s * %s = %s", a, b, res);
  
  free(res);
}
```

And that too with blazing fast speeds! Most of the heavy-lifting of these algorithms is written in x86 assembly in order to maximize its efficiency.

Downloading and using this library is as simple as including the header file (`basic_math_operations.h`), and linking the `libbasic_math_operations.a` file using `-L. -lbasic_math_operations`. Of course, it works with both C and C++, but is primarily _meant_ to be a C library (you'd have to use C-styled strings even in C++).
