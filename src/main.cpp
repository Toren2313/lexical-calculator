#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "./viewModels/Types/enums.h"
#include "./viewModels/Types/structs.h"

#include "./viewModels/Tokenizer/lexer.h"

using namespace std;

int main()
{
    string mOperation;
    lexer l;

    while (true)
    {
        cin >> mOperation;

        l.tokenize(mOperation);
    }

}