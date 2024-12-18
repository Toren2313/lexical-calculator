#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "../Types/enums.h"
#include "../Types/structs.h"

class lexer
{
private:
void printVector(std::vector<Token> v);
std::string tokenTypeToString(TokenType t);
public:
    void tokenize();
};

