//
// Created by 35915 on 24-10-16.
//
#include <iostream>
#include <string>
#include <vector>
#define N 1005

int nums[N] = {0};

int main() {
    std::string cmd;
    std::getline(std::cin, cmd);
    std::vector<int> bracket_indices;
    int index = 0;

    // Preprocess to find matching brackets
    for (int i = 0; i < cmd.size(); i++) {
        if (cmd[i] == '[') {
            bracket_indices.push_back(i);
        } else if (cmd[i] == ']') {
            if (!bracket_indices.empty()) {
                int start = bracket_indices.back();
                bracket_indices.pop_back();
                // Store the start and end indices for quick access later
            } else {
                // Handle unmatched closing bracket if necessary
            }
        }
    }

    // Execute commands
    for (int i = 0; i < cmd.size(); i++) {
        char cur_ch = cmd[i];
        if (cur_ch == '>') {
            index++;
        } else if (cur_ch == '<') {
            index--;
        } else if (cur_ch == '+') {
            nums[index]++;
        } else if (cur_ch == '-') {
            nums[index]--;
        } else if (cur_ch == ',') {
            char ch;
            if (std::cin.get(ch)){
                nums[index] = (int)ch;
            } else {
                nums[index] = 0;
            }
        } else if (cur_ch == '.') {
            std::cout << (char)nums[index];
        } else if (cur_ch == '[') {
            if (nums[index] == 0) {
                // Skip to the corresponding ']'
                int open = 1;
                while (open > 0) {
                    i++;
                    if (cmd[i] == '[') open++;
                    if (cmd[i] == ']') open--;
                }
            }
        } else if (cur_ch == ']') {
            if (nums[index] != 0) {
                // Move back to the corresponding '['
                int close = 1;
                while (close > 0) {
                    i--;
                    if (cmd[i] == '[') close--;
                    if (cmd[i] == ']') close++;
                }
            }
        }
    }
}
