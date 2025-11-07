#include <iostream>
#include <vector>

#include "./parser.hpp"

using ld = long double;

struct Priority {
    int depth, priority;
    Priority(int a, int b) : depth(a), priority(b) {}
    bool operator>(const Priority& other) const {
        if (depth == other.depth) return priority > other.priority;
        return depth > other.depth;
    }
};

struct Node {
    Token token;
    std::optional<Priority> priority;
};

struct Executer {
    void throw_error(std::string code = "Parsing error") {
        std::cerr << code << std::endl;
        exit(EXIT_FAILURE);
    }

    ld add(ld a, ld b) { return a + b; }
    ld sub(ld a, ld b) { return a - b; }
    ld mul(ld a, ld b) { return a * b; }
    ld div(ld a, ld b) {
        if (b == 0) {
            throw_error("Can't divide by zero");
        }
        return a / b;
    }

    ld execute(std::vector<Token> tokens) {
        std::vector<Node> res;

        int depth = 0;
        for (Token token : tokens) {
            if (token.type == Tokens::open_par) {
                depth++;
            } else if (token.type == Tokens::close_par) {
                depth--;
            } else if (token.type == Tokens::num_lit) {
                if (!token.value.has_value()) throw_error();
                res.push_back({ .token=token });
            } else if (token.type == Tokens::plus || token.type == Tokens::minus) {
                res.push_back({ token, Priority(depth, 0) });
            } else if (token.type == Tokens::multi || token.type == Tokens::divide) {
                res.push_back({ token, Priority(depth, 1) });
            } else {
                throw_error();
            }
        }

        while (res.size() > 1) {
            size_t maxi = -1;
            for (size_t i = 0; i < res.size(); i++) {
                if (res[i].priority.has_value()) {
                    if (maxi == -1 || res[i].priority.value() > res[maxi].priority.value()) {
                        maxi = i;
                    }
                }
            }
            if (maxi == -1) throw_error();
            if (maxi == 0 || maxi == res.size() - 1) throw_error();
            if (
                res[maxi].token.type != Tokens::plus
                && res[maxi].token.type != Tokens::minus
                && res[maxi].token.type != Tokens::multi
                && res[maxi].token.type != Tokens::divide
            ) throw_error();
            if (res[maxi - 1].token.type != Tokens::num_lit) throw_error();
            if (res[maxi + 1].token.type != Tokens::num_lit) throw_error();

            ld x = 0;
            if (res[maxi].token.type == Tokens::plus) {
                x = add(res[maxi - 1].token.value.value(), res[maxi + 1].token.value.value());
            } else if (res[maxi].token.type == Tokens::minus) {
                x = sub(res[maxi - 1].token.value.value(), res[maxi + 1].token.value.value());
            } else if (res[maxi].token.type == Tokens::multi) {
                x = mul(res[maxi - 1].token.value.value(), res[maxi + 1].token.value.value());
            } else if (res[maxi].token.type == Tokens::divide) {
                x = div(res[maxi - 1].token.value.value(), res[maxi + 1].token.value.value());
            } else {
                throw_error();
            }
            res[maxi - 1] = { .token={ .type=Tokens::num_lit, .value=x } };
            res.erase(res.begin() + maxi + 1);
            res.erase(res.begin() + maxi);
        }

        if (res[0].token.type != Tokens::num_lit) {
            throw_error();
        } else {
            return res[0].token.value.value();
        }

        return 0;
    }

    Executer() {}
};