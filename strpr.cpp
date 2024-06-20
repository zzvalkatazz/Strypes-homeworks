#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>

// Structure to represent an integrated circuit
struct IntegratedCircuit {
    std::string name;
    std::vector<std::string> inputs;
    std::string expression;
};

// Structure to represent input values
struct InputValue {
    std::string name;
    int value;
};

bool isAlphanumeric(char c) {
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9');
}

bool parseDefineCommand(const std::string& command, IntegratedCircuit& ic) {
    std::string definePart = "DEFINE ";
    if (command.substr(0, definePart.size()) != definePart) {
        return false;
    }
    std::string remaining = command.substr(definePart.size());

    // Extracting name and inputs
    size_t nameEnd = remaining.find('(');
    if (nameEnd == std::string::npos) {
        return false;
    }
    ic.name = remaining.substr(0, nameEnd);
    size_t inputsEnd = remaining.find(')');
    if (inputsEnd == std::string::npos) {
        return false;
    }
    std::string inputsStr = remaining.substr(nameEnd + 1, inputsEnd - nameEnd - 1);

    // Remove leading and trailing spaces from inputsStr
    size_t startPos = 0;
    size_t endPos = inputsStr.length() - 1;
    while (startPos <= endPos && std::isspace(inputsStr[startPos])) {
        startPos++;
    }
    while (endPos >= startPos && std::isspace(inputsStr[endPos])) {
        endPos--;
    }
    inputsStr = inputsStr.substr(startPos, endPos - startPos + 1);

    // Split inputs by comma
    size_t pos = 0;
    while ((pos = inputsStr.find(',')) != std::string::npos) {
        ic.inputs.push_back(inputsStr.substr(0, pos));
        inputsStr.erase(0, pos + 1);
        // Remove leading and trailing spaces for the next input
        while (!inputsStr.empty() && std::isspace(inputsStr[0])) {
            inputsStr.erase(0, 1);
        }
    }

    // Add the last input
    ic.inputs.push_back(inputsStr);

    // Extracting expression
    size_t exprStart = remaining.find(':', inputsEnd);
    if (exprStart == std::string::npos) {
        return false;
    }
    ic.expression = remaining.substr(exprStart + 2);

    // Replace '^' with '!'
    std::replace(ic.expression.begin(), ic.expression.end(), '^', '!');

    // Check if all inputs are defined
    size_t posInput = 0;
    std::string inputName;
    while (posInput < ic.expression.length()) {
        if (isAlphanumeric(ic.expression[posInput])) {
            inputName.clear();
            while (posInput < ic.expression.length() && isAlphanumeric(ic.expression[posInput])) {
                inputName += ic.expression[posInput];
                posInput++;
            }
            if (std::find(ic.inputs.begin(), ic.inputs.end(), inputName) == ic.inputs.end()) {
                std::cout << "Error: Input '" << inputName << "' is not defined.\n";
                return false;
            }
        }
        else {
            posInput++;
        }
    }
    return true;
}

int precedence(char op) {
    if (op == '!') return 3;
    if (op == '&') return 2;
    if (op == '|') return 1;
    return 0;
}

bool applyOp(char op, bool a, bool b) {
    switch (op) {
    case '&': return a && b;
    case '|': return a || b;
    default: return false;
    }
}

bool evaluateExpression(const std::string& expression, const std::vector<InputValue>& inputValues, bool& result) {
    std::stack<bool> values;
    std::stack<char> ops;
    std::string token;
    size_t pos = 0;

    while (pos < expression.size()) {
        if (isspace(expression[pos])) {
            pos++;
            continue;
        }

        if (expression[pos] == '(') {
            ops.push(expression[pos]);
        }
        else if (expression[pos] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                char op = ops.top(); ops.pop();
                bool val2 = values.top(); values.pop();
                bool val1 = values.top(); values.pop();
                values.push(applyOp(op, val1, val2));
            }
            ops.pop();
        }
        else if (expression[pos] == '&' || expression[pos] == '|') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[pos])) {
                char op = ops.top(); ops.pop();
                bool val2 = values.top(); values.pop();
                bool val1 = values.top(); values.pop();
                values.push(applyOp(op, val1, val2));
            }
            ops.push(expression[pos]);
        }
        else if (expression[pos] == '!') {
            ops.push(expression[pos]);
        }
        else if (isAlphanumeric(expression[pos])) {
            token.clear();
            while (pos < expression.size() && isAlphanumeric(expression[pos])) {
                token += expression[pos++];
            }
            pos--;
            auto it = std::find_if(inputValues.begin(), inputValues.end(), [&token](const InputValue& iv) {
                return iv.name == token;
                });
            if (it == inputValues.end()) {
                std::cout << "Error: Undefined input '" << token << "' in expression.\n";
                return false;
            }
            values.push(it->value);
        }
        pos++;
    }

    while (!ops.empty()) {
        char op = ops.top(); ops.pop();
        if (op == '!') {
            bool val = values.top(); values.pop();
            values.push(!val);
        }
        else {
            bool val2 = values.top(); values.pop();
            bool val1 = values.top(); values.pop();
            values.push(applyOp(op, val1, val2));
        }
    }

    if (values.size() != 1) {
        std::cout << "Error: Invalid expression evaluation.\n";
        return false;
    }

    result = values.top();
    return true;
}

void runCommand(const std::string& command, const std::vector<IntegratedCircuit>& circuits) {
    std::string runPart = "RUN ";
    if (command.substr(0, runPart.size()) != runPart) {
        std::cout << "Error: Invalid RUN command.\n";
        return;
    }
    std::string remaining = command.substr(runPart.size());

    // Extracting circuit name and input values
    size_t nameEnd = remaining.find('(');
    if (nameEnd == std::string::npos) {
        std::cout << "Error: Invalid circuit name or inputs.\n";
        return;
    }
    std::string circuitName = remaining.substr(0, nameEnd);
    size_t inputsEnd = remaining.find(')');
    if (inputsEnd == std::string::npos) {
        std::cout << "Error: Invalid circuit name or inputs.\n";
        return;
    }
    std::string inputsStr = remaining.substr(nameEnd + 1, inputsEnd - nameEnd - 1);

    // Split input values by comma
    std::vector<int> inputValues;
    size_t pos = 0;
    while (pos < inputsStr.length()) {
        size_t commaPos = inputsStr.find(',', pos);
        if (commaPos == std::string::npos) {
            commaPos = inputsStr.length();
        }
        std::string inputValueStr = inputsStr.substr(pos, commaPos - pos);
        inputValues.push_back(std::stoi(inputValueStr));
        pos = commaPos + 1;
    }

    // Find the circuit definition
    auto it = std::find_if(circuits.begin(), circuits.end(), [&circuitName](const IntegratedCircuit& ic) {
        return ic.name == circuitName;
        });
    if (it == circuits.end()) {
        std::cout << "Error: Circuit '" << circuitName << "' is not defined.\n";
        return;
    }

    // Check if the number of input values matches the number of defined inputs
    if (inputValues.size() != it->inputs.size()) {
        std::cout << "Error: Incorrect number of input values for circuit '" << circuitName << "'.\n";
        return;
    }

    // Create a vector of input names and their values
    std::vector<InputValue> inputMap;
    for (size_t i = 0; i < it->inputs.size(); ++i) {
        InputValue iv;
        iv.name = it->inputs[i];
        iv.value = inputValues[i];
        inputMap.push_back(iv);
    }

    // Evaluate the circuit's expression
    bool result;
    if (evaluateExpression(it->expression, inputMap, result)) {
        std::cout << "Result: " << (result ? "1" : "0") << "\n";
    }
    else {
        std::cout << "Error: Failed to evaluate the expression.\n";
    }
}

void allCommand(const std::string& command, const std::vector<IntegratedCircuit>& circuits) {
    std::string allPart = "ALL ";
    if (command.substr(0, allPart.size()) != allPart) {
        std::cout << "Error: Invalid ALL command.\n";
        return;
    }
    std::string circuitName = command.substr(allPart.size());

    // Find the circuit definition
    auto it = std::find_if(circuits.begin(), circuits.end(), [&circuitName](const IntegratedCircuit& ic) {
        return ic.name == circuitName;
        });
    if (it == circuits.end()) {
        std::cout << "Error: Circuit '" << circuitName << "' is not defined.\n";
        return;
    }

    size_t inputCount = it->inputs.size();
    size_t combinations = std::pow(2, inputCount);

    for (size_t i = 0; i < combinations; ++i) {
        std::vector<InputValue> inputMap;
        for (size_t j = 0; j < inputCount; ++j) {
            InputValue iv;
            iv.name = it->inputs[j];
            iv.value = (i >> j) & 1;
            inputMap.push_back(iv);
        }

        // Evaluate the circuit's expression
        bool result;
        if (evaluateExpression(it->expression, inputMap, result)) {
            std::cout << "Inputs: ";
            for (size_t j = 0; j < inputCount; ++j) {
                std::cout << it->inputs[j] << "=" << ((i >> j) & 1) << " ";
            }
            std::cout << "Result: " << (result ? "1" : "0") << "\n";
        }
        else {
            std::cout << "Error: Failed to evaluate the expression.\n";
        }
    }
}

int main() {
    std::vector<IntegratedCircuit> circuits;
    std::string command;

    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        if (command.find("DEFINE") == 0) {
            IntegratedCircuit ic;
            if (parseDefineCommand(command, ic)) {
                circuits.push_back(ic);
            }
            else {
                std::cout << "Error: Invalid DEFINE command.\n";
            }
        }
        else if (command.find("RUN") == 0) {
            runCommand(command, circuits);
        }
        else if (command.find("ALL") == 0) {
            allCommand(command, circuits);
        }
        else {
            std::cout << "Error: Invalid command.\n";
        }
    }

    return 0;
}
