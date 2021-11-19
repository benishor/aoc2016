#include "solution.h"
#include <regex>


class day10 : public aoc::solution {
protected:

    enum class instruction_type {
        give_to_bot,
        give_to_output
    };

    struct bot {
        std::set<int> microchips;
        instruction_type low_instruction;
        int low_target_id{-1};
        instruction_type high_instruction;
        int high_target_id{-1};
    };

    std::map<int, bot> bots;
    std::map<int, int> outputs;

    int solve_part_1(int start_id) {
        std::set<int> bots_to_check = {start_id};

        while (!bots_to_check.empty()) {
            std::set<int> next_bots_to_check;
            for (auto id : bots_to_check) {
                bot& b = bots[id];
                if (b.microchips.size() < 2) continue;
                if (*b.microchips.cbegin() == 17 && *b.microchips.crbegin() == 61) return id;
                switch (b.low_instruction) {
                    case instruction_type::give_to_bot:
                        bots[b.low_target_id].microchips.insert(*b.microchips.cbegin());
                        next_bots_to_check.insert(b.low_target_id);
                        break;
                    case instruction_type::give_to_output:
                        outputs[b.low_target_id] = *b.microchips.cbegin();
                        break;
                }
                switch (b.high_instruction) {
                    case instruction_type::give_to_bot:
                        bots[b.high_target_id].microchips.insert(*b.microchips.crbegin());
                        next_bots_to_check.insert(b.high_target_id);
                        break;
                    case instruction_type::give_to_output:
                        outputs[b.high_target_id] = *b.microchips.crbegin();
                        break;
                }
                bots[id].microchips.clear();
            }
            bots_to_check = next_bots_to_check;
        }
        return -1;
    }

    int solve_part_2(int start_id) {
        std::set<int> bots_to_check = {start_id};

        while (!bots_to_check.empty()) {
            std::set<int> next_bots_to_check;
            for (auto id : bots_to_check) {
                bot& b = bots[id];
                if (b.microchips.size() < 2) continue;
                switch (b.low_instruction) {
                    case instruction_type::give_to_bot:
                        bots[b.low_target_id].microchips.insert(*b.microchips.cbegin());
                        next_bots_to_check.insert(b.low_target_id);
                        break;
                    case instruction_type::give_to_output:
                        outputs[b.low_target_id] = *b.microchips.cbegin();
                        break;
                }
                switch (b.high_instruction) {
                    case instruction_type::give_to_bot:
                        bots[b.high_target_id].microchips.insert(*b.microchips.crbegin());
                        next_bots_to_check.insert(b.high_target_id);
                        break;
                    case instruction_type::give_to_output:
                        outputs[b.high_target_id] = *b.microchips.crbegin();
                        break;
                }
                bots[id].microchips.clear();
            }
            bots_to_check = next_bots_to_check;
        }
        return -1;
    }

    void run(std::istream& in, std::ostream& out) override {

        const std::regex initRegex{R"(value (\d+) goes to bot (\d+))"};
        const std::regex giveBotsRegex{R"(bot (\d+) gives low to bot (\d+) and high to bot (\d+))"};
        const std::regex giveToOutputAndBotRegex{R"(bot (\d+) gives low to output (\d+) and high to bot (\d+))"};
        const std::regex giveToOutputsRegex{R"(bot (\d+) gives low to output (\d+) and high to output (\d+))"};

        for (std::string line; std::getline(in, line);) {
            std::smatch matches;
            if (std::regex_match(line, matches, initRegex)) {
                auto bot_id = std::stoi(matches.str(2));
                auto value = std::stoi(matches.str(1));
                bots[bot_id].microchips.insert(value);
            } else if (std::regex_match(line, matches, giveBotsRegex)) {
                auto& bot = bots[std::stoi(matches.str(1))];
                bot.low_instruction = instruction_type::give_to_bot;
                bot.low_target_id = std::stoi(matches.str(2));
                bot.high_instruction = instruction_type::give_to_bot;
                bot.high_target_id = std::stoi(matches.str(3));
            } else if (std::regex_match(line, matches, giveToOutputAndBotRegex)) {
                auto& bot = bots[std::stoi(matches.str(1))];
                bot.low_instruction = instruction_type::give_to_output;
                bot.low_target_id = std::stoi(matches.str(2));
                bot.high_instruction = instruction_type::give_to_bot;
                bot.high_target_id = std::stoi(matches.str(3));
            } else if (std::regex_match(line, matches, giveToOutputsRegex)) {
                auto& bot = bots[std::stoi(matches.str(1))];
                bot.low_instruction = instruction_type::give_to_output;
                bot.low_target_id = std::stoi(matches.str(2));
                bot.high_instruction = instruction_type::give_to_output;
                bot.high_target_id = std::stoi(matches.str(3));
            } else {
                std::cerr << "Could not parse line " << line << std::endl;
            }
        }

        for (auto& kv : bots) {
            if (kv.second.microchips.size() == 2) {
                std::cout << solve_part_2(kv.first) << std::endl;
                std::cout << "out[0] = " << outputs[0] << " , out[1] = " << outputs[1] << ", out[2] = " << outputs[2] << std::endl;
                break;
            }
        }
    }
};

int main(int argc, char **argv) {
    day10 solution{};
    return solution.execute(argc, argv);
}
