#include "expressionSplit.h"


std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool isElementaryFunction(const std::string& func) {
    return elementaryFunctions.find(func) != elementaryFunctions.end() 
    || func.rfind("log_", 0) == 0 || func.rfind("root_", 0) == 0;

}

std::vector<std::string> decomposeNestedFunctions(const std::string& func, const std::string& arg) {
    std::vector<std::string> decomposed;
    
    std::string currentArg = arg;
    
    // Start by decomposing the outermost function
    decomposed.push_back(func + "(" + currentArg + ")");
    
    // Continue decomposing until the argument is fully broken down
    while (std::regex_match(currentArg, std::regex(R"((\w+)\(([^)]+)\))"))) {
        std::smatch match;
        std::regex_search(currentArg, match, std::regex(R"((\w+)\(([^)]+)\))"));
        
        std::string innerFunc = match.str(1);  // The function name
        std::string innerArg = match.str(2);   // The argument inside the function
        
        // Add the next level of decomposition
        decomposed.push_back(innerFunc + "(" + innerArg + ")");
        currentArg = innerArg;
    }

    return decomposed;
}

std::vector<std::string> splitByOperators(const std::string& expr) {
    std::vector<std::string> terms;
    std::string currentTerm;
    int parenCount = 0;

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (c == '(') parenCount++;
        if (c == ')') parenCount--;

        if ((c == '+' || c == '-' || c == '*' || c == '/' || c == '^') && parenCount == 0) {
            if (!currentTerm.empty()) {
                terms.push_back(trim(currentTerm));
                currentTerm.clear();
            }
            currentTerm += c; // Add operator as part of the next term
        } else {
            currentTerm += c;
        }
    }

    if (!currentTerm.empty()) {
        terms.push_back(trim(currentTerm));
    }

    return terms;
}

std::vector<std::string> parseElementaryFunctions(const std::string& term) {
    std::vector<std::string> subterms;
    std::regex functionPattern(R"((\w+)\(([^)]+)\))");      // Matches functions like sin(x), ln(x), arcsin(x)
    std::regex logBasePattern(R"(log_(\d+)\(([^)]+)\))");  // Matches log_base(f(x)) e.g. log_2(x)
    std::regex nthRootPattern(R"(root_(\d+)\(([^)]+)\))"); // Matches root_n(f(x)) e.g. root_3(x)
    std::smatch match;

    std::string tempTerm = term;

    // Handle root_n case first
    while (std::regex_search(tempTerm, match, nthRootPattern)) {
        std::string rootDegree = match.str(1);  // The root degree, e.g., "3" for cube root
        std::string argument = match.str(2);    // The argument inside parentheses, e.g., "x"
        
        subterms.push_back("root_" + rootDegree + "(" + argument + ")");
        
        // Decompose nested functions inside root_n
        std::vector<std::string> nestedTerms = decomposeNestedFunctions("root_" + rootDegree, argument);
        subterms.insert(subterms.end(), nestedTerms.begin(), nestedTerms.end());

        tempTerm = match.suffix();  // Continue with the rest of the term
    }
    
    // Handle log_base case
    while (std::regex_search(tempTerm, match, logBasePattern)) {
        std::string base = match.str(1);   // The base, e.g., "2"
        std::string argument = match.str(2);  // The argument inside parentheses, e.g., "x"
        
        subterms.push_back("log_" + base + "(" + argument + ")");
        
        // Decompose nested functions inside log_base
        std::vector<std::string> nestedTerms = decomposeNestedFunctions("log_" + base, argument);
        subterms.insert(subterms.end(), nestedTerms.begin(), nestedTerms.end());

        tempTerm = match.suffix();  // Continue with the rest of the term
    }
    
    // Now handle other functions
    while (std::regex_search(tempTerm, match, functionPattern)) {
        std::string functionName = match.str(1);  // The function name, e.g., "sin", "arcsin"
        std::string argument = match.str(2);      // The argument inside parentheses, e.g., "x"

        if (isElementaryFunction(functionName)) {
            // Decompose nested functions
            std::vector<std::string> nestedTerms = decomposeNestedFunctions(functionName, argument);
            subterms.insert(subterms.end(), nestedTerms.begin(), nestedTerms.end());
        } else {
            subterms.push_back(match.str(0));  // Handle unknown cases as general function calls
        }
        tempTerm = match.suffix();  // Continue with the rest of the term
    }

    if (!tempTerm.empty()) {
        subterms.push_back(tempTerm);  // Add remaining part of term
    }

    return subterms;
}

std::vector<std::string> parseExpression(const std::string& expr) {
    // Step 1: Split by top-level operators (+, -, *, /, ^)
    std::vector<std::string> terms = splitByOperators(expr);
    std::vector<std::string> allTerms;

    // Step 2: Further decompose terms if they contain elementary functions or complex expressions
    for (const std::string& term : terms) {
        // Check for elementary functions or expressions involving parentheses
        std::vector<std::string> subterms = parseElementaryFunctions(term);

        // Add all subterms to the final list
        for (const std::string& subterm : subterms) {
            allTerms.push_back(subterm);
        }
    }

    return allTerms;
}

