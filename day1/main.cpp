#include "solution.h"

enum direction {
    north,
    east,
    south,
    west
};

class day1 : public aoc::solution {
protected:

    int32_t current_x{0};
    int32_t current_y{0};
    uint8_t facing{north};

    void turn_left() {
        facing = facing == 0 ? 3 : facing - 1;
    }

    void turn_right() {
        facing = facing == 3 ? 0 : facing + 1;
    }

    void advance(size_t amount) {
        switch (facing) {
            case north:
                current_y -= amount;
                break;
            case east:
                current_x += amount;
                break;
            case south:
                current_y += amount;
                break;
            case west:
                current_x -= amount;
                break;
        }
    }

    uint64_t encode_position() const {
        return static_cast<uint64_t>(static_cast<uint32_t>(current_x)) << 32ULL |
               static_cast<uint64_t>(static_cast<uint32_t>(current_y));
    }

    uint64_t current_distance() const {
        return abs(current_x) + abs(current_y);
    }

    void run(std::istream& in, std::ostream& out) override {
        std::map<uint64_t, uint32_t> visited_locations;
        visited_locations[encode_position()]++;

        bool part2_found{false};
        uint64_t part2_distance{0};

        for (std::string line; std::getline(in, line, ',');) {
            line = aoc::trim(line);
            if (line[0] == 'L') {
                turn_left();
            } else {
                turn_right();
            }
            auto blocks = std::stoi(line.substr(1));
            for (auto i = 0; i < blocks; i++) {
                advance(1);
                auto position = encode_position();
                visited_locations[position]++;
                if (!part2_found && visited_locations[position] == 2) {
                    part2_found = true;
                    part2_distance = current_distance();
                }
            }
        }

        out << current_distance() << std::endl;
        out << part2_distance << std::endl;
    }
};

int main(int argc, char **argv) {
    day1 solution{};
    return solution.execute(argc, argv);
}
