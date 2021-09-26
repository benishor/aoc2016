#include "solution.h"

class day9 : public aoc::solution {
protected:

    size_t size_of_basic_decode(std::string line) {
        bool in_marker{false};
        bool reading_a{false};
        std::string a;
        std::string b;
        size_t how_many_to_skip{0};
        size_t length{0};

        for (auto c: line) {
            if (c == '\t' || c == '\n' || c == '\r' || c == ' ') continue;

            if (in_marker) {
                if (c == 'x') {
                    reading_a = false;
                } else if (c == ')') {
                    in_marker = false;
                    int aa = std::stoi(a);
                    int bb = std::stoi(b);
                    how_many_to_skip = aa;
                    length += aa * bb;
                } else {
                    if (reading_a) {
                        a += c;
                    } else {
                        b += c;
                    }
                }
            } else {
                if (how_many_to_skip > 0) {
                    how_many_to_skip--;
                } else {
                    if (c == '(') {
                        in_marker = true;
                        reading_a = true;
                        a = "";
                        b = "";
                    } else {
                        length++;
                    }
                }
            }
        }
        return length;
    }

    size_t size_of_improved_decode(std::string line) {
        bool in_marker{false};
        bool reading_a{false};
        std::string a;
        std::string b;
        size_t how_many_to_skip{0};
        std::string subchunk;
        size_t length{0};
        int aa{0};
        int bb{0};

        for (auto c: line) {
            if (c == '\t' || c == '\n' || c == '\r' || c == ' ') continue;

            if (in_marker) {
                if (c == 'x') {
                    reading_a = false;
                } else if (c == ')') {
                    in_marker = false;
                    aa = std::stoi(a);
                    bb = std::stoi(b);
                    how_many_to_skip = aa;
                    subchunk = "";
                } else {
                    if (reading_a) {
                        a += c;
                    } else {
                        b += c;
                    }
                }
            } else {
                if (how_many_to_skip > 0) {
                    subchunk += c;
                    how_many_to_skip--;
                    if (how_many_to_skip == 0) {
                        length += bb * size_of_improved_decode(subchunk);
                    }
                } else {
                    if (c == '(') {
                        in_marker = true;
                        reading_a = true;
                        a = "";
                        b = "";
                    } else {
                        length++;
                    }
                }
            }
        }
        return length;
    }

    void run(std::istream &in, std::ostream &out) override {
        std::string line;
        std::getline(in, line);

        out << size_of_basic_decode(line) << std::endl;
        out << size_of_improved_decode(line) << std::endl;
    }
};

int main(int argc, char **argv) {
    day9 solution{};
    return solution.execute(argc, argv);
}
