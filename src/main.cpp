#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "./viewModels/Types/enums.h"
#include "./viewModels/Types/structs.h"

#include "./viewModels/Tokenizer/lexer.h"

using namespace std;

int main() {
    string mOperation;
    lexer l;

    while (true) {
        cin >> mOperation;

        l.tokenize(mOperation);
    }
}
