#include "./lexer.h"

using namespace std;

void lexer::printVector(vector<Token> v) {
    for (Token &t : v) {
        cout << tokenTypeToString(t.token) + ": " << t.value << endl;
    }
}

string lexer::tokenTypeToString(TokenType t) {
    switch (t) {
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::MULTIPLICATION:
        return "MULTIPLICATION";
    case TokenType::DIVIDE:
        return "DIVIDE";
    case TokenType::POWER:
        return "POWER";
    case TokenType::PERCENT:
        return "PERCENT";
    case TokenType::NUMBER:
        return "NUMBER";
    default:
        return "invalid";
    }
}

std::vector<Token> lexer::tokenize(std::string operation) {
    std::vector<Token> tokens;
    std::string currentNumber;

    for (char c : operation) {
        if (isspace(c)) {
            continue;
        } else if (isdigit(c)) {
            currentNumber += c;
        } else {
            if (!currentNumber.empty()) {
                tokens.push_back({TokenType::NUMBER, currentNumber});
                currentNumber.clear();
            }
            switch (c) {
            case 'x':
#if defined(_WIN32) || defined(_WIN64)
                system("cls");
#else
                system("clear");
#endif
                break;
            case '+':
                tokens.push_back({TokenType::PLUS, std::string(1, c)});
                break;
            case '-':
                tokens.push_back({TokenType::MINUS, std::string(1, c)});
                break;
            case '*':
                tokens.push_back({TokenType::MULTIPLICATION, std::string(1, c)});
                break;
            case '/':
                tokens.push_back({TokenType::DIVIDE, std::string(1, c)});
                break;
            case '^':
                tokens.push_back({TokenType::POWER, std::string(1, c)});
                break;
            case '%':
                tokens.push_back({TokenType::PERCENT, std::string(1, c)});
                break;
            default:
                break;
            }
        }
    }

    if (!currentNumber.empty()) {
        tokens.push_back({TokenType::NUMBER, currentNumber});
    }

    printVector(tokens);
    return tokens;
}

int lexer::calculate(std::vector<Token> tokens) {
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
