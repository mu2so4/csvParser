#include <tuple>
#include <iostream>
#include "parser.h"
#include "tuple_io.h"

int main() {
    int skip;
    std::string filename;
    std::cin >> skip >> filename;

    std::ifstream in(filename);
    std::ofstream out("output.txt");
    csv::CSVParser<int, int, std::string> parser{in, skip};

    for(auto & iter : parser) {
        out << iter << '\n';
    }
    return 0;
}
