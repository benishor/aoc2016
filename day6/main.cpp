#include "solution.h"

enum class frequency_type {
    most,
    least
};

static std::string most_frequent_letters(const std::vector<std::map<char, int>>& frequencies, frequency_type type) {
    using pair_type = std::map<char, int>::value_type;

    std::stringstream out;
    for (auto& i: frequencies) {
        auto x = std::max_element(std::begin(i), std::end(i), [type](const pair_type& a, const pair_type& b) {
            return type == frequency_type::most ? a.second < b.second : b.second < a.second;
        });
        out << x->first;
    }
    return out.str();
}

class day6 : public aoc::solution {
protected:

    void run(std::istream& in, std::ostream& out) override {
        std::vector<std::map<char, int>> frequencies;
        for (std::string line; std::getline(in, line);) {
            if (frequencies.empty()) {
                frequencies.resize(line.size());
            }
            for (size_t i = 0; i < line.size(); i++) {
                frequencies[i][line[i]]++;
            }
        }

        out << most_frequent_letters(frequencies, frequency_type::most) << std::endl;
        out << most_frequent_letters(frequencies, frequency_type::least) << std::endl;
    }
};

int main(int argc, char **argv) {
    day6 solution{};
    return solution.execute(argc, argv);
}
