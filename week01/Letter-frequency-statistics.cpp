#include <iostream>
#include <algorithm>
#include <string>

int main() {
    int q;
    std::cin >> q;
    int arr[26] = {0};
    std::string command;
    std::string word;
    for (int i = 0; i < q; i++) {
        std::cin >> command;
        if (std::equal(command.begin(), command.end(), "add")) {
            std::cin >> word;
            for (char ch: word) {
                arr[ch - 'a']++;
            }
        } else if (std::equal(command.begin(), command.end(), "query")) {
            int max = 0;
            for (int j = 0; j < 26; j++) {
                max = max < arr[j] ? arr[j] : max;
            }
            if (max != 0) {
                for (int j = 0; j < 26; j++) {
                    if (arr[j] == max) {
                        std::cout << char('a' + j);
                    }
                }
            }
            std::cout << '\n';
        }
    }
}