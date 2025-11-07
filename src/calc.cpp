#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "./executer.hpp"

int main(int argc, char* argv[]) {
    std::string input;
    if (argc == 2) {
        std::ifstream fd(argv[1]);
        if (!fd.is_open()) {
            std::cerr << "File not found" << std::endl;
            return EXIT_FAILURE;
        }
        std::getline(fd, input);
        fd.close();
    } else if (argc == 1) {
        std::getline(std::cin, input);
    } else {
        std::cerr << "Invalid arguments" << std::endl;
    }

    Parser parser;
    std::vector<Token> tokens = parser.parse(input);

    Executer executer;
    ld x = executer.execute(tokens);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << x << std::endl;
}