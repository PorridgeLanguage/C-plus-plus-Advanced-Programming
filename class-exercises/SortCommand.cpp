#include <bits/stdc++.h>

std::vector<std::string> arr;

void print_arr() {
    for (auto item : arr) {
        std::cout << item << "\n";
    }
}

bool compare_(std::string& a, std::string& b) {
    return a < b;
}

bool compare_n(std::string& a, std::string& b) {
    std::stringstream ss_a(a);
    std::stringstream ss_b(b);
    int a_num, b_num;
    ss_a >> a_num;
    ss_b >> b_num;
    return a_num < b_num;
}

bool compare_i(std::string& a, std::string& b) {
    int len = a.size() < b.size() ? a.size() : b.size();
    for (int i = 0; i < len; i++) {
        char ch_a = a[i], ch_b = b[i];
        if (std::isalpha(ch_a) && std::isalpha(ch_b)) {
            ch_a = std::tolower(ch_a);
            ch_b = std::tolower(ch_b);
            if (ch_a != ch_b) {
                return ch_a < ch_b;
            }
        }
    }
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    return a < b;
}

bool compare_d(std::string& a, std::string& b) {
    std::string copy_a = "";
    std::string copy_b = "";
    for (char ch : a) {
        if (std::isalpha(ch) || std::isdigit(ch) || ch == ' ') {
            copy_a += ch;
        }
    }
    for (char ch : b) {
        if (std::isalpha(ch) || std::isdigit(ch) || ch == ' ') {
            copy_b += ch;
        }
    }
    return copy_a < copy_b;
}

bool compare_r(std::string& a, std::string& b) {
    return a > b;
}

int main() {
    std::size_t N;
    std::cin >> N;
    std::cin >> std::ws;
    for (int i = 0; i < N; i++) {
        std::string line;
        std::getline(std::cin, line);
        arr.push_back(line);
    }
    int C;
    std::cin >> C;

    for (int i = 0; i < C; i++) {
        char ch;
        std::cin >> ch;
        switch (ch) {
            case '-':
                std::sort(arr.begin(), arr.end(), compare_);
                break;
            case 'n':
                std::sort(arr.begin(), arr.end(), compare_n);
                break;
            case 'i':
                std::sort(arr.begin(), arr.end(), compare_i);
                break;
            case 'd':
                std::sort(arr.begin(), arr.end(), compare_d);
                break;
            case 'r':
                std::sort(arr.begin(), arr.end(), compare_r);
                break;
            default:
                break;
        }
        print_arr();
    }
}