#include "./lexer.h"

using namespace std;

Lexer::Lexer(string operation, bool debugMode) {
    this->tokens = this->tokenize(operation);
    if (this->syntaxAnalyzer() == false)
        throw runtime_error("invalid syntax");
    if (debugMode)
        this->printVector();

       this->tokensRPN = this->inFixToRPN();

    // cout << "Result is: " << r << endl;
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
            case '(':
            case ')': {
                tokens.push_back({TokenType::_OPERATOR, std::string(1, c)});
                break;
            }

            case 'x':
#if defined(_WIN32) || defined(_WIN64)
                system("cls");
#else
                system("clear");
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
    if (t == "*" || t == "/")
        return 1;
    if (t == "^" || t == "%")
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
            output.push_back({TokenType::_OPERATOR, t.value});
        else if (t.token == TokenType::_OPERATOR && t.value == "(")
            ops.push(t.value);
        else if (t.token == TokenType::_OPERATOR && t.value == ")") {
            while (ops.top() != "(") {
                output.push_back({TokenType::_OPERATOR, ops.top()});
                ops.pop();
            }
            ops.pop();

        } else if (t.token == TokenType::_OPERATOR) {
            while (!ops.empty() && precedence(t.value) <= precedence(ops.top())) {
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
    if (this->tokens.empty())
        return false;

    bool expectingNumber = true;

    for (Token &t : this->tokens) {

        if (t.token == TokenType::NUMBER && expectingNumber) {
            expectingNumber = false;
        } else if (t.token == TokenType::_OPERATOR && !expectingNumber) {
            expectingNumber = true;
        } else {
            return false;
        }
    }
    if (expectingNumber) {
        return false;
    }
    return true;
}

int Lexer::evalRPN() {
    stack<int> rpnStack;
    int result;

    for (Token &t : this->tokens) {
        if (t.token == TokenType::NUMBER) {
            cout << "pushed: " << t.value << endl;
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
/*
int Lexer::calculate(std::vector<Token> tokens) {
    if (tokens.empty()) {
        cout << "no aritmetic operation found.";
        exit(-1);
    }

    if (!this->syntaxAnalyzer(tokens)) {
        cout << "invalid syntax." << endl;
        exit(-1);
    }

    int result = 0;
    int currentNumber = 0;
    TokenType lastOperator = TokenType::PLUS;

    for (Token &t : tokens) {
        if (t.token == TokenType::NUMBER) {
            // currentNumber = currentNumber * 10 + (t.value - '0'); // char -> int
            to_string(currentNumber);
        } else {
            switch (lastOperator) {
            case TokenType::PLUS:
                result += currentNumber;
                break;
            case TokenType::MINUS:
                result -= currentNumber;
                break;
            case TokenType::MULTIPLICATION:
                result *= currentNumber;
                break;
            case TokenType::DIVIDE:
                if (currentNumber != 0) {
                    result /= currentNumber;
                } else {
                    cout << "err: divide by 0" << endl;
                    return 0;
                }
                break;
            default:
                break;
            }
            lastOperator = t.token;
            currentNumber = 0;
        }
    }

    switch (lastOperator) {
    case TokenType::PLUS:
        result += currentNumber;
        break;
    case TokenType::MINUS:
        result -= currentNumber;
        break;
    case TokenType::MULTIPLICATION:
        result *= currentNumber;
        break;
    case TokenType::DIVIDE:
        if (currentNumber != 0) {
            result /= currentNumber;
        } else {
            cout << "err: divide by 0" << endl;
            return 0;
        }
        break;
    default:
        break;
    }

    return result;
}
*/
