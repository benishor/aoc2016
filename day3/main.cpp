#include "solution.h"
#include <regex>

class day3 : public aoc::solution {
protected:

    static bool is_valid_triangle(int a, int b, int c) {
        if ((a + b) <= c) return false;
        if ((a + c) <= b) return false;
        if ((b + c) <= a) return false;
        return true;
    }

    static int count_horizontal_triangles(const std::vector<std::vector<int>>& data) {
        int result{0};
        for (auto& line: data) {
            result += is_valid_triangle(line[0], line[1], line[2]);
        }
        return result;
    }

    static int count_vertical_triangles(const std::vector<std::vector<int>>& data) {
        int result{0};
        size_t triangles_per_cols = data.size() / 3;
        for (size_t i = 0; i < triangles_per_cols; i++) {
            for (size_t j = 0; j < data[0].size(); j++) {
                result += is_valid_triangle(data[i * 3 + 0][j], data[i * 3 + 1][j], data[i * 3 + 2][j]);
            }
        }
        return result;
    }

    void run(std::istream& in, std::ostream& out) override {

        const std::regex sidesRegex{R"(\s*(\d+)\s*(\d+)\s*(\d+)\s*)"};

        std::vector<std::vector<int>> data;
        for (std::string line; std::getline(in, line);) {
            std::smatch matches;
            if (std::regex_match(line, matches, sidesRegex)) {
                int a = std::stoi(matches.str(1));
                int b = std::stoi(matches.str(2));
                int c = std::stoi(matches.str(3));
                data.push_back({a, b, c});
            } else {
                std::cerr << "Unparsable input line [" << line << "]" << std::endl;
            }
        }

        out << std::to_string(count_horizontal_triangles(data)) << std::endl;
        out << std::to_string(count_vertical_triangles(data)) << std::endl;
    }
};

int main(int argc, char **argv) {
    day3 solution{};
    return solution.execute(argc, argv);
}
