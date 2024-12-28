#pragma once
#include <algorithm>
#include <iostream>
#include <math.h>
#include <stack>
#include <string>
#include <vector>

#include "../Types/enums.h"
#include "../Types/structs.h"

class Lexer {
  private:
    /**
     * displays tokens (as vector) in console
     * @return void
     */
    void printVector();

    /**
     * Convert TokenType to string
     *
     * @param t TokenType
     * @return TokenType as string
     *
     * example: TokenType::MINUS return string "MINUS"
     */
    std::string tokenTypeToString(TokenType t);

    /**
     * Checks if there is no error in the syntax
     *
     * @return true or false (bool)
     */
    bool syntaxAnalyzer();

    std::vector<Token> tokens;
    std::vector<Token> tokensRPN;

    /**
     *
     */
    std::vector<Token> tokenize(std::string operation);

    /**
     * Evals arithmetic operation by Reverse Polish Notation (RPN)
     *
     * @return result of arithmetic operation (as int)
     */
    int evalRPN();

    /**
     * Converts infix operation to RPN  (Reverse Polish Notation)
     */
    std::vector<Token> inFixToRPN();

  public:
    Lexer(std::string operation, bool debugMode);
};
