# SmartCalc v1.0

## Introduction

In this project, I implemented an extended version of the usual calculator, which can be found in the standard applications of each operating system in the C programming language using structured programming. In addition to basic arithmetic operations such as addition/subtraction and multiplication/division, I have supplemented the calculator with the ability to calculate arithmetic expressions following the order, as well as some mathematical functions (sine, cosine, logarithm, etc.).

In addition to calculating expressions, it also supports using the _x_ variable and plotting the corresponding function.

A loan calculator was also implemented.

## Information

- **Arithmetic operators**:

    | Operator name | Infix notation <br /> (Classic) | Prefix notation <br /> (Polish notation) |  Postfix notation <br /> (Reverse Polish notation) |
    | --------- | ------ | ------ | ------ |
    | Brackets | (a + b) | (+ a b) | a b + |
    | Addition | a + b | + a b | a b + |
    | Subtraction | a - b | - a b | a b - |
    | Multiplication | a * b | * a b | a b * |
    | Division | a / b | / a b | a b \ |
    | Power | a ^ b | ^ a b | a b ^ |
    | Modulus | a mod b | mod a b | a b mod |
    | Unary plus | +a | +a | a+ |
    | Unary minus | -a | -a | a- |

- **Functions**:

    | Function description | Function |
    | ------ | ------ |
    | Computes cosine | cos(x) |
    | Computes sine | sin(x) |
    | Computes tangent | tan(x) |
    | Computes arc cosine | acos(x) |
    | Computes arc sine | asin(x) |
    | Computes arc tangent | atan(x) |
    | Computes square root | sqrt(x) |
    | Computes natural logarithm | ln(x) |
    | Computes common logarithm | log(x) |


## Credit calculator

Provide a special mode "credit calculator":
- Input: total credit amount, term, interest rate, type (annuity, differentiated)
- Output: monthly payment, overpayment on credit, total payment