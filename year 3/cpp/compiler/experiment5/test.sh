#!/bin/bash

# Test script for the arithmetic expression parser

echo "Testing Arithmetic Expression Parser"
echo "===================================="
echo

# Test 1: Simple expression
echo "Test 1: Simple arithmetic expression"
echo "Input: x = a + b"
echo "x = a + b" | ./arithmetic
echo

# Test 2: Complex expression with numbers
echo "Test 2: Complex expression with numbers"
echo "Input: result = (alpha + beta) * 3.14 - gamma / 2.5"
echo "result = (alpha + beta) * 3.14 - gamma / 2.5" | ./arithmetic
echo

# Test 3: Expression with invalid characters
echo "Test 3: Expression with invalid characters"
echo "Input: x = a + b $ invalid"
echo "x = a + b $ invalid" | ./arithmetic
echo

# Test 4: Only identifiers
echo "Test 4: Only identifiers"
echo "Input: alpha beta gamma"
echo "alpha beta gamma" | ./arithmetic
echo

# Test 5: Only numbers
echo "Test 5: Only numbers and operators"
echo "Input: 42 + 3.14 * 2.71"
echo "42 + 3.14 * 2.71" | ./arithmetic
echo

echo "All tests completed!"