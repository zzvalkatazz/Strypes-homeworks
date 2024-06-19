#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

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
    if (nameEnd >= remaining.length()) {
        return false;
    }
    ic.name = remaining.substr(0, nameEnd);
    size_t inputsEnd = remaining.find(')');
    if (inputsEnd >= remaining.length()) {
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
    if (exprStart >= remaining.length()) {
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
bool evaluateExpression(const std::string& expression, const std::vector<InputValue>& inputValues, bool& result) {
    // Evaluate logical expression with input values
    std::string logicalExpression = expression;

    // Replace input names with their values
    for (const InputValue& input : inputValues) {
        size_t pos = 0;
        while ((pos = logicalExpression.find(input.name, pos)) != std::string::npos) {
            logicalExpression.replace(pos, input.name.length(), std::to_string(input.value));
            pos += std::to_string(input.value).length();
        }
    }

    // Replace '!' with 'n' for easier tokenization
    std::replace(logicalExpression.begin(), logicalExpression.end(), '!', 'n');

    // Tokenize the logical expression
    std::vector<std::string> tokens;
    std::string token;
    size_t start = 0;
    size_t end = 0;

    while (end < logicalExpression.size()) {
        if (std::isspace(logicalExpression[end])) {
            if (start != end) {
                tokens.push_back(logicalExpression.substr(start, end - start));
            }
            start = ++end;
        }
        else if (logicalExpression[end] == '&' || logicalExpression[end] == '|' || logicalExpression[end] == 'n') {
            if (start != end) {
                tokens.push_back(logicalExpression.substr(start, end - start));
            }
            tokens.push_back(logicalExpression.substr(end, 1));
            start = ++end;
        }
        else {
            end++;
        }
    }
    if (start != end) {
        tokens.push_back(logicalExpression.substr(start, end - start));
    }

    // Perform logical evaluation
    bool operand1, operand2;
    bool intermediateResult = false; // Store intermediate results

    if (tokens.size() == 1) { // Single operand (e.g., "true" or "false")
        if (tokens[0] == "true" || tokens[0] == "1") {
            result = true;
            return true;
        }
        else if (tokens[0] == "false" || tokens[0] == "0") {
            result = false;
            return true;
        }
        else {
            return false; // Invalid expression
        }
    }

    // Process in pairs
    operand1 = (tokens[0] == "true" || tokens[0] == "1") ? true : false;
    for (size_t i = 1; i < tokens.size(); i += 2) {
        operand2 = (tokens[i + 1] == "true" || tokens[i + 1] == "1") ? true : false;
        if (tokens[i] == "&") { // AND operation
            intermediateResult = operand1 && operand2;
        }
        else if (tokens[i] == "|") { // OR operation
            intermediateResult = operand1 || operand2;
        }
        else if (tokens[i] == "n") { // NOT operation
            intermediateResult = !operand2; // Invert operand2
        }
        operand1 = intermediateResult;
    }

    result = intermediateResult;
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
    std::vector<IntegratedCircuit>::const_iterator it = std::find_if(circuits.begin(), circuits.end(), [&circuitName](const IntegratedCircuit& ic) {
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

    // Create a vector of InputValue representing input names and their values
    std::vector<InputValue> inputMap;
    for (size_t i = 0; i < it->inputs.size(); ++i) {
        inputMap.push_back({ it->inputs[i], inputValues[i] });
    }

    // Evaluate the circuit's expression
    bool result;
    if (evaluateExpression(it->expression, inputMap, result)) {
        std::cout << "Result: " << (result ? "true" : "false") << "\n";
    }
    else {
        std::cout << "Error: Failed to evaluate the expression.\n";
    }
}

int main() {
    std::vector<IntegratedCircuit> circuits;

    while (true) {
        std::string command;
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        if (command.find("DEFINE") == 0) {
            IntegratedCircuit ic;
            if (parseDefineCommand(command, ic)) {
                circuits.push_back(ic);
                std::cout << "Circuit '" << ic.name << "' defined successfully.\n";
            }
            else {
                std::cout << "Error: Invalid DEFINE command.\n";
            }
        }
        else if (command.find("RUN") == 0) {
            runCommand(command, circuits);
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            std::cout << "Error: Unknown command.\n";
        }
    }

    return 0;
}

