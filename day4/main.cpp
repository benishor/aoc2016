#include "solution.h"

struct room {
    std::string name;
    int id;
    std::string checksum;

    [[nodiscard]] bool is_valid() const {
        return compute_checksum() == checksum;
    }

    [[nodiscard]] std::string decode() const {
        std::stringstream out;
        for (auto c: name) {
            if (c == '-')
                out << ' ';
            else
                out << (char) ((((c - 'a') + id) % 26) + 'a');
        }
        return out.str();
    }

    [[nodiscard]] std::string compute_checksum() const {
        std::unordered_map<char, int> frequency;
        for (auto c: name) {
            if (c != '-') {
                frequency[c]++;
            }
        }
        std::map<int, std::set<char>> frequencyToChars;
        for (auto& kv: frequency) {
            frequencyToChars[kv.second].insert(kv.first);
        }

        std::stringstream result;
        int chars_in_checksum{0};
        for (auto it = frequencyToChars.crbegin(); it != frequencyToChars.crend() && chars_in_checksum < 5; it++) {
            for (auto i: it->second) {
                result << i;
                chars_in_checksum++;
                if (chars_in_checksum == 5) break;
            }
        }

        return result.str();
    }
};

class day4 : public aoc::solution {
protected:


    void run(std::istream& in, std::ostream& out) override {

        std::vector<room> rooms;

        const std::regex roomRegex{R"((.*)-(\d+)\[(.*)\])"};
        for (std::string line; std::getline(in, line);) {
            std::smatch matches;
            if (std::regex_match(line, matches, roomRegex)) {
                rooms.emplace_back(room{
                        .name = matches.str(1),
                        .id = std::stoi(matches.str(2)),
                        .checksum = matches.str(3)
                });
            } else {
                std::cerr << "Failed to parse line " << line << std::endl;
            }
        }

        uint32_t part1{0};
        uint32_t part2{0};
        for (auto& r: rooms) {
            if (r.is_valid()) {
                part1 += r.id;
                auto decoded_name = r.decode();
                if (decoded_name.find("orth") != std::string::npos &&
                    decoded_name.find("ole") != std::string::npos &&
                    decoded_name.find("bject") != std::string::npos) {
                    part2 = r.id;
                }
            }
        }
        out << part1 << std::endl;
        out << part2 << std::endl;
    }
};


int main(int argc, char **argv) {
    day4 solution{};
    return solution.execute(argc, argv);
}
