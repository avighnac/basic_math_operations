<h1 align='center'>basic_math_operations</h1>

> A biginteger library for both Windows and Linux written in Assembly and C that can be used in C++, C, and Python.

<p align='center'>
Explore the <a href='https://github.com/avighnac/basic_math_operations/wiki'><strong>docs</strong></a>
</p>

Have you ever wanted to add, subtract, or multiply huge numbers but your calculator or favourite programming language only gives you an approximation?

For example, let's say you wanted to, for some reason, multiply `387261987198787123479468764398` by `1897346897629873468761342`. These numbers are extremely huge, and would be a programmatic nightmare to deal with. Well, that is, without this library.

Here's how simple it becomes with basic_math_operations.

## Python
```py
import basic_math_operations as bmo

a = '387261987198787123479468764398'
b = '1897346897629873468761342'

res = bmo.multiply(a, b)

print(res)
```

## C
```c
#include "basic_math_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char a[] = "387261987198787123479468764398";
  char b[] = "1897346897629873468761342";
  
  char *res = (char *)calloc(strlen(a) + strlen(b) + 1, 1);
  multiply(a, b, res);
  
  printf("%s * %s = %s\n", a, b, res);
  
  free(res);
}
```

And that too with blazing-fast speeds! Most of the heavy lifting of these algorithms is written in x86 assembly in order to maximize their efficiency.

Downloading and using this library is as simple as including the header file (`basic_math_operations.h` or `basic_math_operations.hpp`), and linking the `libbasic_math_operations.a` file using `-L. -lbasic_math_operations`.

# Installation
## Python
To install the module `basic_math_operations`, you can use pip (for Python >= 3.10). You can also manually install it from [here](https://pypi.org/project/basic-math-operations/) if that doesn't work for you.

And you're done! Now you'll be able to import the library into your Python programs using this line: `import basic_math_operations`.

## C/C++
If you're on Linux, you'll be able to install this library and copy its headers to `/usr/include` by executing a single shell command.

```shell
curl -s -H "Accept: application/vnd.github.v3.raw" https://api.github.com/repos/avighnac/basic_math_operations/contents/install.sh | sudo bash
```

# Compilation
Here's a full example of compiling a program made using `basic_math_operations`.
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
  printf("Enter the first number: ");
  scanf("%1023s", a);
  printf("Enter the second number: ");
  scanf("%1023s", b);

  char* res = (char *)calloc(strlen(a) + strlen(b) + 43, 1);

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

When allocating memory for the result buffer, use `calloc()` and not `malloc()` (for `calloc`, you can use malloc syntax, just add `1` as its second argument). This is because `calloc()` zeroes the allocated memory for you: you could also use `malloc()` and zero the memory yourself.

The functions higher up in each of their respective sections are *usually* faster than their lower counterparts. If you know that two numbers will have the same length, using the specialized function will be faster.

Detailed information for each of these functions can be found in the `basic_math_operations.h` file. This is just a brief.

(Note that the windows version of this library doesn't have functions to add and subtract numbers of the same length as of now. Calling these functions on windows will certainly cause your application to throw a segmentation fault.)

Addition:
- `add_whole_same_length()` adds two non-negative integers of the same length.
- `add_whole()` adds two non-negative integers.
- `addp()` adds two non-negative rational numbers.
- `add()` adds two rational numbers.

Subtraction:
All subtract functions can return a negative number, but only some can take negative numbers as input. All of them also subtract the second argument from the first argument.
- `subtract_whole_same_length()` subtracts two non-negative integers of the same length.
- `subtract_whole()` subtracts two non-negative integers.
- `subtractp()` subtracts two non-negative rational numbers.
- `subtract()` subtracts two rational numbers.

Multiplication:
- `multiply_whole()` multiplies two non-negative integers.
- `multiplyp()` multiplies two non-negative rational numbers.
- `multiply()` multiplies two rational numbers.

Division:
All division functions divide the first argument by the second argument.
- `divide_whole_with_remainder()` performs modular division on the input.
- `divide_whole()` divides two non-negative integers.
- `dividep()` divides two non-negative rational numbers.
- `divide()` divides two rational numbers.
