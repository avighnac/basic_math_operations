%ifdef __MACH__
  %define _Divide_whole_with_remainder __divide_whole_with_remainder
  %define _Multiply_whole __multiply_whole
  %define Add_whole_same_length _add_whole_same_length
  %define Add_whole _add_whole
  %define Addp _addp
  %define Asmalloc _asmalloc
  %define Multiply_whole _multiply_whole
  %define Remove_leading_zeroes _remove_leading_zeroes
  %define Remove_leading_zeroes_inplace _remove_leading_zeroes_inplace
  %define Strlen_asm _strlen_asm
  %define Subtract_whole_same_length _subtract_whole_same_length
  %define Subtract_whole _subtract_whole
  %define Subtractp _subtractp
  %define CALL(func) call func
%else
  %define _Divide_whole_with_remainder _divide_whole_with_remainder
  %define _Multiply_whole _multiply_whole
  %define Add_whole_same_length add_whole_same_length
  %define Add_whole add_whole
  %define Addp addp
  %define Asmalloc asmalloc
  %define Multiply_whole multiply_whole
  %define Remove_leading_zeroes remove_leading_zeroes
  %define Remove_leading_zeroes_inplace remove_leading_zeroes_inplace
  %define Strlen_asm strlen_asm
  %define Subtract_whole_same_length subtract_whole_same_length
  %define Subtract_whole subtract_whole
  %define Subtractp subtractp
  %define CALL(func) call func wrt ..plt
%endif