#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "./viewModels/Types/enums.h"
#include "./viewModels/Types/structs.h"

#include "./viewModels/Lexer/lexer.h"

using namespace std;

int main() {
    string mOperation;

    while (true) {
        cout << ">> ";
        getline(cin, mOperation);

        Lexer l(mOperation, false);
    }
}
