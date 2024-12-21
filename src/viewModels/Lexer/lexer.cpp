#include "./lexer.h"

using namespace std;

Lexer::Lexer(string operation, bool debugMode) {
    this->tokens = this->tokenize(operation);
    if (this->syntaxAnalyzer() == false) {
        throw runtime_error("invalid syntax.");
    }
    if (debugMode) {
        this->printVector();

        cout << "Debug: Lexer constructor finished." << endl;
    }
};
void Lexer::printVector() {
    for (Token &t : this->tokens) {
        cout << this->tokenTypeToString(t.token) + ": " << t.value << endl;
    }
}
string Lexer::tokenTypeToString(TokenType t) {
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
std::vector<Token> Lexer::tokenize(std::string operation) {

    std::string currentNumber;
    vector<Token> tokens;

    for (char c : operation) {
        if (isspace(c)) {
            continue;
        } else if (isdigit(c)) {
            currentNumber += c;
            continue;
        } else {
            if (!currentNumber.empty()) {
                tokens.push_back({TokenType::NUMBER, currentNumber});
                currentNumber.clear();
            }
            switch (c) {
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
bool Lexer::syntaxAnalyzer() {
    if (this->tokens.empty())
        return false;

    bool expectingNumber = true;

    vector<TokenType> types = {TokenType::PLUS,   TokenType::MINUS,   TokenType::MULTIPLICATION,
                               TokenType::DIVIDE, TokenType::PERCENT, TokenType::POWER};

    for (Token &t : this->tokens) {
        if (t.token == TokenType::NUMBER && expectingNumber) {
            expectingNumber = false;
        } else if (std::find(types.begin(), types.end(), t.token) != types.end() && !expectingNumber) {
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
