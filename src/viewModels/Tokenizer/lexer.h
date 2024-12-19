#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../Types/enums.h"
#include "../Types/structs.h"

class lexer {
  private:
    void printVector(std::vector<Token> v);
    std::string tokenTypeToString(TokenType t);

  public:
    std::vector<Token> tokenize(std::string operation);

  public:
    int calculate(std::vector<Token> tokens);
};
