#include <bits/stdc++.h>

typedef struct floor {
    int bits;
    unsigned long long num;
    std::string num_string;
} floor_t;

std::vector<floor_t> floors;

void addFloor(floor_t new_floor) {
    floors.push_back(new_floor);
}

void deleteFloor(unsigned long long num) {
    for (int i = 0; i < floors.size(); i++) {
        if (floors[i].num == num) {
            floors.erase(floors.begin() + i);
            break;
        }
    }
}

void printFloors() {
    int max_len = 0;
    for (int i = 0; i < floors.size(); i++) {
        max_len = std::max(max_len, floors[i].bits);
    }
    int line_len = 0;
    for (int i = 0; i < floors.size(); i++) {
        if (line_len == 0) {
            std::cout << "0x";
        }
        if (line_len + floors[i].bits < max_len) {
            std::cout << std::hex << floors[i].num;
            line_len += floors[i].bits;
        } else if (line_len + floors[i].bits == max_len) {
            std::cout << std::hex << floors[i].num << "\n";
            line_len = 0;
        } else {
            while (line_len++ < max_len) {
                std::cout << "C";
            }
            std::cout << "\n";
            line_len = 0;
            i--;
        }
    }
    if (line_len != 0) {
        while (line_len++ < max_len) {
            std::cout << "C";
        }
        std::cout << "\n";
    }
}

void specialPrint(int addr, int len) {
    int max_len = 0;
    for (int i = 0; i < floors.size(); i++) {
        max_len = std::max(max_len, floors[i].bits);
    }
    int line_len = 0;
    std::vector<std::string> outputstream;
    std::string temp = "";
    for (int i = 0; i < floors.size(); i++) {
        if (line_len + floors[i].bits < max_len) {
            temp += floors[i].num_string.substr(2);
            line_len += floors[i].bits;
        } else if (line_len + floors[i].bits == max_len) {
            temp += floors[i].num_string.substr(2);
            outputstream.push_back(temp);
            temp = "";
            line_len = 0;
        } else {
            while (line_len++ < max_len) {
                temp += "C";
            }
            outputstream.push_back(temp);
            temp = "";
            line_len = 0;
            i--;
        }
    }
    if (line_len != 0) {
        while (line_len++ < max_len) {
            temp += "C";
        }
        outputstream.push_back(temp);
    }

    int start = addr * 2;
    len = len * 2;
    int count = 0;
    std::cout << "0x";
    for (auto str : outputstream) {
        for (char ch : str) {
            if (count >= start && count < start + len) {
                std::cout << ch;
            }
            count++;
        }
    }
    while (count++ < start + len) {
        std::cout << "C";
    }
    std::cout << "\n";
}

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();
    for (int i = 0; i < n; i++) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string operate;
        ss >> operate;
        if (operate == "add") {
            unsigned long long num, temp;
            std::string num_string;
            ss >> num_string;
            std::stringstream ss(num_string);
            ss >> std::hex >> num;
            num_string.substr(2);
            temp = num;
            int bits = 0;
            while (temp > 0) {
                bits++;
                temp /= 16;
            }
            floor_t new_floor;
            new_floor.bits = bits;
            new_floor.num = num;
            new_floor.num_string = num_string;
            addFloor(new_floor);
        } else if (operate == "del") {
            unsigned long long num;
            ss >> std::hex >> num;
            deleteFloor(num);
        } else if (operate == "print") {
            int addr, len;
            if (ss >> addr >> len) {
                specialPrint(addr, len);
            } else {
                printFloors();
            }
        }
    }
}