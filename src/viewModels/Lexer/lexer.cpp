#include "./lexer.h"
#include "../../main.cpp"

using namespace std;

Lexer::Lexer(string operation, bool debugMode) {
    this->tokens = this->tokenize(operation);
    if (this->syntaxAnalyzer() == false)
        throw runtime_error("invalid syntax");
    if (debugMode)
        this->printVector();

    int r = this->evalRPN(inFixToRPN());

    cout << "Result is: " << r << endl;
};
void Lexer::printVector() {
    for (Token &t : this->tokens) {
        cout << this->tokenTypeToString(t.token) + ": " << t.value << endl;
    }
}
string Lexer::tokenTypeToString(TokenType t) {
    switch (t) {
    case TokenType::_OPERATOR:
        return "OPERATOR";
    case TokenType::NUMBER:
        return "NUMBER";
    case TokenType::RESULT:
        return "RESULT";
    default:
        return "invalid";
    }
}
std::vector<Token> Lexer::tokenize(std::string operation) {
    std::string currentNumber;
    vector<Token> tokens;

    for (char c : operation) {
        if (isspace(c)) {
            if (!currentNumber.empty()) {
                tokens.push_back({TokenType::NUMBER, currentNumber});
                currentNumber.clear();
            }
            continue;
        } else if (isdigit(c)) {
            currentNumber += c;
        } else {
            if (!currentNumber.empty()) {
                tokens.push_back({TokenType::NUMBER, currentNumber});
                currentNumber.clear();
            }
            switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case '%':
            case '(':
            case ')': {
                tokens.push_back({TokenType::_OPERATOR, std::string(1, c)});
                break;
            }

            case 'x':
#ifdef _WIN32
                system("cls");
                main();

#else
                system("clear");
                main();
#endif
                break;
            default:
                break;
            }
        }
    }

    if (!currentNumber.empty()) {
        tokens.push_back({TokenType::NUMBER, currentNumber});
    }

    return tokens;
}

int precedence(string t) {
    if (t == "+" || t == "-")
        return 0;
    if (t == "*" || t == "/" || t == "%")
        return 1;
    if (t == "^")
        return 2;
    if (t == "(" || t == ")")
        return 3;

    return -1;
}

vector<Token> Lexer::inFixToRPN() {
    vector<Token> output;
    stack<string> ops;
    for (Token &t : this->tokens) {
        if (t.token == TokenType::NUMBER)
            output.push_back({TokenType::NUMBER, t.value});
        else if (t.value == "(") {
            ops.push("(");
        } else if (t.value == ")") {
            while (!ops.empty() && ops.top() != "(") {
                output.push_back({TokenType::_OPERATOR, ops.top()});
                ops.pop();
            }
            if (!ops.empty()) {
                ops.pop();
            }
        } else {
            while (!ops.empty() && precedence(t.value) <= precedence(ops.top()) && ops.top() != "(") {
                output.push_back({TokenType::_OPERATOR, ops.top()});
                ops.pop();
            }
            ops.push(t.value);
        }
    }
    while (!ops.empty()) {
        output.push_back({TokenType::_OPERATOR, ops.top()});
        ops.pop();
    }

    for (auto &v : output) {
        cout << v.value << endl;
    }

    return output;
}

bool Lexer::syntaxAnalyzer() {
    stack<string> stack;
    if (this->tokens.empty())
        return false;

    bool expectingNumber = true;

    for (Token &t : this->tokens) {
        if (t.value == "(") {
            stack.push(t.value);
            expectingNumber = true;
        } else if (t.value == ")") {
            if (stack.empty()) {
                cout << "empty" << endl;
                return false;
            }
            stack.pop();
            expectingNumber = false;
        } else if (t.token == TokenType::NUMBER && expectingNumber) {
            expectingNumber = false;
        } else if (t.token == TokenType::_OPERATOR && !expectingNumber) {
            expectingNumber = true;
        } else {
            return false;
        }
    }
    if (!stack.empty())
        return false;
    if (expectingNumber)
        return false;

    return true;
}

int Lexer::evalRPN(std::vector<Token> tokensInRPN) {
    stack<int> rpnStack;
    int result;

    for (Token &t : tokensInRPN) {
        if (t.token == TokenType::NUMBER) {
            rpnStack.push(stoi(t.value));
        } else {
            int b = rpnStack.top();
            rpnStack.pop();
            int a = rpnStack.top();
            rpnStack.pop();

            if (t.value == "+") {
                result = a + b;
            } else if (t.value == "-") {
                result = a - b;

            } else if (t.value == "*") {
                result = a * b;

            } else if (t.value == "/") {
                if (b == 0) {
                    throw runtime_error("Division by zero");
                }
                result = a / b;

            } else if (t.value == "^") {
                result = pow(a, b);
            } else if (t.value == "%") {
                result = a % b;
            }
            rpnStack.push(result);
        }
    }

    return rpnStack.top();
}
