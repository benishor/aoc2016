#include "solution.h"
#include "md5.h"

class day5 : public aoc::solution {
protected:

    static std::string part1(const std::string& code) {
        uint32_t index{1};
        uint8_t characters_found{0};
        std::stringstream out;
        while (characters_found < 8) {
            std::stringstream composite_code;
            composite_code << code << std::to_string(index++);
            auto md5 = MD5{composite_code.str()};
            auto md5_hex = md5.hexdigest();
            if (md5_hex.substr(0, 5) == "00000") {
                out << md5_hex.at(5);
                characters_found++;
            }
        }
        return out.str();
    }

    static std::string part2(const std::string& code) {
        uint32_t index{1};
        std::bitset<8> chars_set{0};
        std::string result = "00000000";

        while (chars_set.count() < 8) {
            std::stringstream composite_code;
            composite_code << code << std::to_string(index++);
            auto md5 = MD5{composite_code.str()};
            auto md5_hex = md5.hexdigest();
            if (md5_hex.substr(0, 5) == "00000") {
                auto position = md5_hex.at(5) - '0';
                if (position >= 0 && position < 8 && !chars_set.test(position)) {
                    result[position] = md5_hex.at(6);
                    chars_set.set(position);
                }
            }
        }
        return result;
    }

    void run(std::istream& in, std::ostream& out) override {
        std::string code;
        std::getline(in, code);

        out << part1(code) << std::endl;
        out << part2(code) << std::endl;
    }
};

int main(int argc, char **argv) {
    day5 solution{};
    return solution.execute(argc, argv);
}
