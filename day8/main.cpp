#include "solution.h"
#include <regex>

struct display {

    std::array<std::bitset<50>, 6> pixels;

    display() {
        for (auto &row: pixels) {
            row.reset();
        }
    }

    void rect(int width, int height) {
        for (int i = 0; i < height; i++) {
            for (int x = 0; x < width; x++) {
                pixels[i].set(x);
            }
        }
    }

    void rotateRow(int y, int by) {
        std::bitset<50> new_row;
        for (int x = 0; x < 50; x++) {
            int new_x = x - by;
            if (new_x < 0) new_x += 50;
            new_row.set(x, pixels[y].test(new_x));
        }
        pixels[y] = new_row;
    }

    void rotateCol(int x, int by) {
        std::bitset<6> new_col;
        for (int y = 0; y < 6; y++) {
            int new_y = y - by;
            if (new_y < 0) new_y += 6;
            new_col.set(y, pixels[new_y].test(x));
        }
        for (int y = 0; y < 6; y++) {
            pixels[y].set(x, new_col.test(y));
        }

    }

    void dump(std::ostream &out) {
        for (auto &row: pixels) {
            for (int x = 0; x < 50; x++) {
                out << (row.test(x) ? '#' : '.');
            }
            out << std::endl;
        }
    }

    int countLitPixels() const {
        int result{0};
        for (auto &row: pixels) {
            result += row.count();
        }
        return result;
    }
};

class day8 : public aoc::solution {
protected:

    void run(std::istream &in, std::ostream &out) override {

        const std::regex rectRegex{R"(rect (\d+)x(\d+))"};
        const std::regex rotateRowRegex{R"(rotate row y=(\d+) by (\d+))"};
        const std::regex rotateColRegex{R"(rotate column x=(\d+) by (\d+))"};

        display screen{};
        for (std::string line; std::getline(in, line);) {
            std::smatch matches{};
            if (std::regex_match(line, matches, rectRegex)) {
                screen.rect(std::stoi(matches.str(1)), std::stoi(matches.str(2)));
            } else if (std::regex_match(line, matches, rotateRowRegex)) {
                screen.rotateRow(std::stoi(matches.str(1)), std::stoi(matches.str(2)));
            } else if (std::regex_match(line, matches, rotateColRegex)) {
                screen.rotateCol(std::stoi(matches.str(1)), std::stoi(matches.str(2)));
            } else {
                std::cerr << "Failed to recognise instruction " << line << std::endl;
            }
        }

        screen.dump(out);
        out << screen.countLitPixels() << std::endl;

    }
};

int main(int argc, char **argv) {
    day8 solution{};
    return solution.execute(argc, argv);
}
