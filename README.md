--- Overview ---
This project is a Reverse Polish Notation (RPN) calculator implemented in C++. It evaluates mathematical expressions written in postfix notation without using the C++ Standard Template Library (STL). Each formula is a valid expression in an infix notation with functions and ends with a dot ('.').

--- Features ---
Evaluates expressions in Reverse Polish Notation.

Supports the following operations:
a + b, a - b ;
a * b, a / b - all operations are made on integers, hence the results of division are rounded down (standard C '/' operator). You cannot divide by 0;
IF(a, b, c) -if a>0 return b, otherwise c;
N a -unary negation, i.e. -a;
MIN( a1, a2, ... ), MAX(a1, a2, ...) -functions MIN and MAX do not have a restriction on the number of parameters;
( ... ) -parentheses.
