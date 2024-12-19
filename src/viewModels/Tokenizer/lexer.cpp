#include "./lexer.h"

using namespace std;

void lexer::printVector(vector<Token> v)
{
    for (Token &t : v)
    {
        cout << tokenTypeToString(t.token) + ": " << t.value << endl;
    }
}

string lexer::tokenTypeToString(TokenType t)
{
    switch (t)
    {
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::MULTIPLICATION:
        return "MULTIPLICATION";
    case TokenType::DIVIDE:
        return "DIVIDE";
    case TokenType::NUMBER:
        return "NUMBER";
    default:
        return "invalid";
    }
}

std::vector<Token> lexer::tokenize(std::string operation){
    vector<Token> tokens;
        for (char c : operation)
        {
            if (isspace(c))
                continue;
            switch (c)
            {
            case '+':
                tokens.push_back({TokenType::PLUS, '+'});
                break;
            case '-':
                tokens.push_back({TokenType::MINUS, '-'});
                break;
            case '*':
                tokens.push_back({TokenType::MULTIPLICATION, '*'});
                break;
            case '/':
                tokens.push_back({TokenType::DIVIDE, '/'});
                break;
            default:
                if(isdigit(c)){
                    tokens.push_back({TokenType::NUMBER, c});
                }
                break;
            }
        }
    
    printVector(tokens);

    return tokens;
}