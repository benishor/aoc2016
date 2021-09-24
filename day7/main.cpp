#include "solution.h"

static bool has_tls_support(const std::string& line) {
    size_t i = 0;
    bool in_hypernet{false};
    bool has_abba{false};
    while (i < line.size()) {
        if (line[i] == '[') {
            in_hypernet = true;
        } else if (line[i] == ']') {
            in_hypernet = false;
        } else {
            bool abba_here =
                    i > 2 && line[i] == line[i - 3] && line[i - 1] == line[i - 2] && line[i] != line[i - 1];
            if (abba_here) {
                if (in_hypernet) {
                    return false;
                } else {
                    has_abba = true;
                }
            }
        }
        i++;
    }
    return has_abba;
}

static bool has_ssl_support(const std::string& line) {
    size_t i = 0;
    bool in_hypernet{false};
    std::set<uint16_t> abas;
    std::set<uint16_t> babs;
    while (i < line.size()) {
        if (line[i] == '[') {
            in_hypernet = true;
        } else if (line[i] == ']') {
            in_hypernet = false;
        } else {
            bool aba_here = i > 1 && line[i] == line[i - 2] && std::isalpha(line[i - 1]) && line[i] != line[i - 1];
            if (aba_here) {
                if (in_hypernet) {
                    uint16_t encoding = static_cast<uint16_t>(line[i]) << 8U |
                                        static_cast<uint16_t>(line[i - 1]);
                    if (abas.find(encoding) != abas.end()) return true;
                    babs.insert(encoding);
                } else {
                    uint16_t encoding = static_cast<uint16_t>(line[i - 1]) << 8U |
                                        static_cast<uint16_t>(line[i]);
                    if (babs.find(encoding) != babs.end()) return true;
                    abas.insert(encoding);
                }
            }
        }
        i++;
    }
    return false;
}

class day7 : public aoc::solution {
protected:
    void run(std::istream& in, std::ostream& out) override {
        uint32_t part1{0};
        uint32_t part2{0};
        for (std::string line; std::getline(in, line);) {
            if (has_tls_support(line)) {
                part1++;
            }
            if (has_ssl_support(line)) {
                part2++;
            }
        }
        out << part1 << std::endl;
        out << part2 << std::endl;
    }
};

int main(int argc, char **argv) {
    day7 solution{};
    return solution.execute(argc, argv);
}
