#include <iostream>
#include <string>
#include <vector>
#include <optional>

using ld = long double;

enum Tokens {
    num_lit,
    open_par,
    close_par,
    plus,
    minus,
    multi,
    divide
};

struct Token {
    Tokens type;
    std::optional<ld> value;
};

struct Parser {
    void throw_error(int i) {
        std::cerr << "Syntax error on character " << i << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<Token> parse(std::string& input) {
        std::vector<Token> res;

        size_t i = 0;
        while (i < input.size()) {
            if (std::isspace(input[i])) {
                i++;
            } else if (input[i] == '(') {
                res.push_back({ .type=Tokens::open_par });
                i++;
            } else if (input[i] == ')') {
                res.push_back({ .type=Tokens::close_par });
                i++;
            } else if (input[i] == '+') {
                res.push_back({ .type=Tokens::plus });
                i++;
            } else if (input[i] == '-') {
                res.push_back({ .type=Tokens::minus });
                i++;
            } else if (input[i] == '*') {
                res.push_back({ .type=Tokens::multi });
                i++;
            } else if (input[i] == '/') {
                res.push_back({ .type=Tokens::divide });
                i++;
            } else if (std::isdigit(input[i])) {
                std::string buf;
                buf.push_back(input[i]);
                bool found_point = false;
                i++;
                while (i < input.size() && (std::isdigit(input[i]) || input[i] == '.')) {
                    if (input[i] == '.') {
                        if (found_point) throw_error(i);
                        found_point = true;
                    }
                    buf.push_back(input[i]);
                    i++;
                }
                ld value = std::stold(buf);
                res.push_back({ .type=Tokens::num_lit, .value=value });
            } else {
                throw_error(i);
            }
        }
        return res;
    }

    Parser() {}
};