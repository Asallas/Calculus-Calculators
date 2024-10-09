#include <vector>
#include <regex>
#include <stack>
#include <string>
#include <cctype>
#include <iostream>
#include <unordered_set>

// Set of supported elementary functions
std::unordered_set<std::string> elementaryFunctions = {
    "sinh", "cosh", "tanh", "csch", "sech", "coth", 
    "sin", "cos", "tan", "sec", "csc", "cot",
    "arctan", "arcsin", "arccos",
    "ln", "log", "exp", "sqrt"
};

// Function to trim leading and trailing spaces
std::string trim(const std::string& str);

// Function to check if a string represents an elementary function
bool isElementaryFunction(const std::string& func);

// Recursive function to parse and decompose expressions
std::vector<std::string> parseExpression(const std::string& expr);

// Function to detect elementary functions and recursively parse nested expressions
std::vector<std::string> parseElementaryFunctions(const std::string& term);

// Function to split expressions by operators while handling parentheses
std::vector<std::string> splitByOperators(const std::string& expr);

std::vector<std::string> decomposeNestedFunctions(const std::string& func, const std::string& arg);