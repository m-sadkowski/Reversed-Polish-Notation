# Reversed Polish Notation (RPN) Calculator

This project is a **Reverse Polish Notation (RPN) calculator** implemented in **C++**. It evaluates mathematical expressions written in postfix notation without using the C++ Standard Template Library (STL). Each formula is a valid expression in infix notation with functions and ends with a dot (`.`).

---

## Features

- **Evaluates expressions in Reverse Polish Notation (RPN).**
- Supports the following operations:
  - **Arithmetic Operations**: `a + b`, `a - b`, `a * b`, `a / b` (all operations are performed on integers, and division results are rounded down using the standard C `/` operator).
  - **Conditional Operation**: `IF(a, b, c)` – if `a > 0`, return `b`; otherwise, return `c`.
  - **Unary Negation**: `N a` – returns `-a`.
  - **Functions**:
    - `MIN(a1, a2, ...)` – returns the minimum value among the provided arguments.
    - `MAX(a1, a2, ...)` – returns the maximum value among the provided arguments.
  - **Parentheses**: `( ... )` – used for grouping expressions.
- **Error Handling**: Detects and handles invalid expressions, such as division by zero.

---

## How It Works

The calculator parses and evaluates mathematical expressions written in **postfix notation** (also known as Reverse Polish Notation). It uses a stack-based approach to process the input and compute the result.

### Example Input and Output

#### Input:
```
3 4 + 2 * .
```

#### Output:
```
14
```

#### Explanation:
1. Push `3` onto the stack.
2. Push `4` onto the stack.
3. Pop `4` and `3`, compute `3 + 4 = 7`, and push `7` onto the stack.
4. Push `2` onto the stack.
5. Pop `2` and `7`, compute `7 * 2 = 14`, and push `14` onto the stack.
6. The final result is `14`.

---

## Getting Started

### Prerequisites

- A C++ compiler (e.g., `g++`).
- Basic knowledge of Reverse Polish Notation.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/m-sadkowski/Reversed-Polish-Notation.git
   cd Reversed-Polish-Notation
   ```

2. Compile the program:
   ```bash
   g++ -o rpn_calculator main.cpp
   ```

3. Run the program:
   ```bash
   ./rpn_calculator
   ```

---

## Usage

1. Enter a valid RPN expression followed by a dot (`.`).
2. The program will evaluate the expression and display the result.

### Example Usage

#### Input:
```
5 1 2 + 4 * + 3 - .
```

#### Output:
```
14
```

#### Explanation:
1. Push `5` onto the stack.
2. Push `1` onto the stack.
3. Push `2` onto the stack.
4. Pop `2` and `1`, compute `1 + 2 = 3`, and push `3` onto the stack.
5. Push `4` onto the stack.
6. Pop `4` and `3`, compute `3 * 4 = 12`, and push `12` onto the stack.
7. Pop `12` and `5`, compute `5 + 12 = 17`, and push `17` onto the stack.
8. Push `3` onto the stack.
9. Pop `3` and `17`, compute `17 - 3 = 14`, and push `14` onto the stack.
10. The final result is `14`.

---

## Supported Operations

| Operation       | Syntax          | Example Input       | Example Output |
|-----------------|-----------------|---------------------|----------------|
| Addition        | `a + b`         | `3 4 + .`           | `7`            |
| Subtraction     | `a - b`         | `5 2 - .`           | `3`            |
| Multiplication  | `a * b`         | `3 4 * .`           | `12`           |
| Division        | `a / b`         | `10 3 / .`          | `3`            |
| Conditional     | `IF(a, b, c)`   | `1 2 3 IF .`        | `2`            |
| Unary Negation  | `N a`           | `5 N .`             | `-5`           |
| Minimum         | `MIN(a1, a2, ...)` | `5 3 8 MIN .`     | `3`            |
| Maximum         | `MAX(a1, a2, ...)` | `5 3 8 MAX .`     | `8`            |

---

## Error Handling

The calculator handles the following errors:
- **Division by zero**: Displays an error message and terminates the program.
- **Invalid expressions**: Detects and reports invalid RPN expressions.

---

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- Inspired by the concept of Reverse Polish Notation.
- Built as a learning project for C++ programming.

---

## Contact

For questions or feedback, please reach out to [m-sadkowski](https://github.com/m-sadkowski).

---

Enjoy calculating with RPN! 🚀