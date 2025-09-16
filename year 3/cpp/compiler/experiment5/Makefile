# Makefile for Flex Arithmetic Expression Parser

PROGRAM = arithmetic
LEX_FILE = arithmetic.l
C_FILE = lex.yy.c
EXECUTABLE = arithmetic

# Default target
all: $(EXECUTABLE)

# Generate C code from flex file
$(C_FILE): $(LEX_FILE)
	flex $(LEX_FILE)

# Compile the generated C code
$(EXECUTABLE): $(C_FILE)
	gcc -o $(EXECUTABLE) $(C_FILE) -lfl

# Clean generated files
clean:
	rm -f $(C_FILE) $(EXECUTABLE) lex.yy.c

# Run the program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Test with sample input
test: $(EXECUTABLE)
	echo "x = a + b * 3.14 - (y / 2)" | ./$(EXECUTABLE)
	echo ""
	echo "result = (alpha + beta) * gamma - 42.5" | ./$(EXECUTABLE)

.PHONY: all clean run test