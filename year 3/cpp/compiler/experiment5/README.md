# Arithmetic Expression Parser using Flex

This program uses Flex (Fast Lexical Analyzer) to recognize and parse arithmetic expressions, identifying identifiers, operators, and numbers.

## Features

- Recognizes valid identifiers (variables)
- Detects arithmetic operators (+, -, *, /, %, parentheses)
- Identifies numbers (integers and floating-point)
- Handles assignment operators (=)
- Reports invalid characters
- Removes duplicate identifiers and operators
- Provides detailed parsing output

## Prerequisites

### Windows
- **Flex**: Install from [GnuWin32](http://gnuwin32.sourceforge.net/packages/flex.htm) or use WSL
- **GCC**: Install MinGW-w64 or use WSL
- **Alternative**: Use WSL (Windows Subsystem for Linux)

### Linux/Unix
```bash
# Ubuntu/Debian
sudo apt-get install flex gcc

# CentOS/RHEL
sudo yum install flex gcc

# macOS
brew install flex gcc
```

## How to Compile and Run

### Windows (Easy Way)
1. Double-click `compile_and_run.bat`
2. The script will compile and run the program automatically

### Windows (Manual)
```cmd
flex arithmetic.l
gcc -o arithmetic.exe lex.yy.c
arithmetic.exe
```

### Linux/Unix
```bash
# Using Makefile
make
make run

# Manual compilation
flex arithmetic.l
gcc -o arithmetic lex.yy.c -lfl
./arithmetic

# Run tests
make test
# or
chmod +x test.sh
./test.sh
```

## Usage

1. Run the program
2. Enter an arithmetic expression when prompted
3. Press Enter to see the results

### Example Input/Output

**Input:**
```
x = (a + b) * 3.14 - y / 2
```

**Output:**
```
--- Parsing Input ---
Identifier: x
Assignment: =
Operator: (
Identifier: a
Operator: +
Identifier: b
Operator: )
Operator: *
Number: 3.14
Operator: -
Identifier: y
Operator: /
Number: 2

--- Results ---
✓ Expression parsing completed

Identifiers found (3):
  1. x
  2. a
  3. b
  4. y

Operators found (6):
  1. =
  2. (
  3. +
  4. )
  5. *
  6. -
  7. /

Numbers found (2):
  1. 3.14
  2. 2
```

## Supported Patterns

- **Identifiers**: `[a-zA-Z_][a-zA-Z0-9_]*`
  - Examples: `x`, `variable1`, `_temp`, `myVar`
- **Numbers**: `[0-9]+(\.[0-9]+)?`
  - Examples: `42`, `3.14`, `0.5`
- **Operators**: `+`, `-`, `*`, `/`, `%`, `(`, `)`, `[`, `]`, `{`, `}`
- **Assignment**: `=`

## Files

- `arithmetic.l` - Flex lexical analyzer source
- `compile_and_run.bat` - Windows compilation script
- `Makefile` - Unix/Linux build file
- `test.sh` - Test script with sample expressions
- `README.md` - This documentation

## Troubleshooting

### "flex: command not found"
- Install Flex for your operating system
- On Windows, add Flex to your PATH or use WSL

### "gcc: command not found"
- Install GCC compiler
- On Windows, install MinGW-w64 or use WSL

### Link errors with `-lfl`
- On some systems, use `-ll` instead of `-lfl`
- Or compile without the flag: `gcc -o arithmetic lex.yy.c`

## Extending the Program

To add more features:
1. Modify the regular expressions in the `%%` section
2. Add new token types in the declarations
3. Update the main function to handle new token types

Example additions:
- Logical operators (`&&`, `||`, `!`)
- Comparison operators (`<`, `>`, `<=`, `>=`, `==`, `!=`)
- String literals
- Comments