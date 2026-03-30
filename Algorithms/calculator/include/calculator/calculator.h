#pragma once

#include <string>
#include <string_view>
#include <stack>
#include <stdexcept>

// Exception for syntax errors in mathematical expressions
// Caused by incorrect syntax: mismatched parentheses, invalid characters, incorrectly formatted numbers, etc
class SyntaxError : public std::runtime_error {
public:
    SyntaxError() noexcept :
        std::runtime_error("Syntax error")
    {
    }
};

// Exception for division by zero errors
// Thrown when attempting to divide by zero
class DivisionByZero : public std::runtime_error {
public:
    DivisionByZero() noexcept :
        std::runtime_error("Division by zero")
    {
    }
};

// Calculates a mathematical expression using the Shunting Yard algorithm
// Supports: +, -, *, / operations and parentheses
// DOES NOT SUPPORT UNARY MINUS!
// Supports both space-separated and space-free strings
// Throws: SyntaxError for invalid expressions, DivisionByZero for division by zero
[[nodiscard]] double Calculate(const std::string_view& expression);
