#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

enum class TokenType
{
    PLUS = '+',
    MINUS = '-',
    MULTIPLICATION = '*',
    DIVIDE = '/',
    NUMBER
};
struct Token
{
    TokenType token;
    char value;
};

string tokenTypeToString(TokenType t)
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
        break;
    }
}

bool isOperator(char c)
{
    static std::map<char, TokenType> tokenMap = {
        {'+', TokenType::PLUS},
        {'-', TokenType::MINUS},
        {'*', TokenType::MULTIPLICATION},
        {'/', TokenType::DIVIDE}};

    return tokenMap.find(c) != tokenMap.end();
}

void printVector(vector<Token> v)
{
    for (Token &t : v)
    {
        cout << t.value << endl;
    }
}

int main()
{
    string mOperation;
    vector<Token> tokens;
    while (true)
    {
        cin >> mOperation;
        for (char c : mOperation)
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
                printVector(tokens);
                break;
            }
        }
    }
}