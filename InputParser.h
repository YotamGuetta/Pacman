#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
const enum gameMode { Empty, save, load, silent, error };
class InputParser {
public:
    InputParser(int& argc, char** argv) {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    int getInput() {
        std::string str;
        if (tokens.size() == 0) {
            return Empty;
        }
        else {
            str = *(this->tokens.begin());
            if (str == "-save" &&( tokens.size() == 1 || (this->tokens[1] == "silent" && tokens.size() == 2))) {
                return save;
            }
            else if (str == "-load") {
                if (tokens.size() == 1) {
                    return load;
                }
                else {
                    str = (this->tokens[1]);
                    if (str == "-silent" && tokens.size() == 2)
                        return silent;

                }

            }
        }
        return error;
    }
    bool cmdOptionExists(const std::string& option) const {
        return std::find(this->tokens.begin(), this->tokens.end(), option)
            != this->tokens.end();
    }
private:
    std::vector <std::string> tokens;
};
