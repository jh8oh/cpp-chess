#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

#include "chess.h"

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit | ios::failbit);
    Chess chess = Chess();
    try {
        return chess.start();
    } catch (ios::failure &) {
        // Any I/O failure quits
        return 1;
    }
}