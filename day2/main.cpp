#include "solution.h"

class day2 : public aoc::solution {
protected:

    static std::string part1(const std::vector<std::string>& lines) {
        uint8_t number{5};
        std::stringstream out;
        for (auto& line: lines) {
            for (auto c: line) {
                switch (c) {
                    case 'U':
                        if (number > 3) number -= 3;
                        break;
                    case 'D':
                        if (number < 7) number += 3;
                        break;
                    case 'L':
                        if (((number - 1) % 3) > 0) number--;
                        break;
                    case 'R':
                        if (((number - 1) % 3) < 2) number++;
                        break;
                    default:
                        std::cerr << "Unexpected char " << c << std::endl;
                        break;
                }
            }
            out << std::to_string(number);
        }
        return out.str();
    }

    static std::string part2(const std::vector<std::string>& lines) {
        char symbols[5][5] = {
                {'\0', '\0', '1', '\0', '\0'},
                {'\0', '2',  '3', '4',  '\0'},
                {'5',  '6',  '7', '8',  '9'},
                {'\0', 'A',  'B', 'C',  '\0'},
                {'\0', '\0', 'D', '\0', '\0'},
        };
        int current_row = 2;
        int current_col = 0;

        std::stringstream out;
        for (auto& line: lines) {
            for (auto c: line) {
                switch (c) {
                    case 'U':
                        if (current_row > 0 && symbols[current_row - 1][current_col] != '\0') current_row--;
                        break;
                    case 'D':
                        if (current_row < 4 && symbols[current_row + 1][current_col] != '\0') current_row++;
                        break;
                    case 'L':
                        if (current_col > 0 && symbols[current_row][current_col - 1] != '\0') current_col--;
                        break;
                    case 'R':
                        if (current_col < 4 && symbols[current_row][current_col + 1] != '\0') current_col++;
                        break;
                    default:
                        std::cerr << "Unexpected char " << c << std::endl;
                        break;
                }
            }
            out << symbols[current_row][current_col];
        }
        return out.str();
    }

    void run(std::istream& in, std::ostream& out) override {
        std::vector<std::string> lines;
        for (std::string line; std::getline(in, line);) {
            lines.push_back(line);
        }

        out << part1(lines) << std::endl;
        out << part2(lines) << std::endl;
    }

    void register_tests() override {
        add_test(aoc::test{
                .name = "First",
                .input = "ULL\n"
                         "RRDDD\n"
                         "LURDL\n"
                         "UUUUD",
                .expected_output = "1985\n5DB3"
        });
    }
};

int main(int argc, char **argv) {
    day2 solution{};
    return solution.execute(argc, argv);
}
