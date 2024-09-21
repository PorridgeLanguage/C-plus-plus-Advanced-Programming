# include <iostream>
# include <string>

int main() {
    int k;
    std::string content;
    std::cin >> content;
    std::cin >> k;
    std::string new_string = "";
    for (char ch : content) {
        if (ch != '-') {
            new_string += std::toupper(ch);
        }
    }
    int len = new_string.end() - new_string.begin();
    
    if (len % k != 0 && len / k + 1 < k) {
        std::cout << "INVALID" << '\n';
        return 0;
    }
    std::string res_string = "";
    int num = len % k;
    num = num == 0 ? k : num;
    int m = 0, n = 1;
    bool found_letter = false;
    bool found_number = false;
    for (int i = 0; i < len; i++) {
        m++;
        char ch = new_string[i];
        res_string += ch;
        if (n == k) {           
            if (m == num) {
                res_string += '-';
                m = 0;
                n++;
            }
        } else {
            if (ch <= 'Z' && ch >= 'A') found_letter = true;
            if (ch <= '9' && ch >= '0') found_number = true;
            if (m == k) {
                if (found_letter && found_number) {
                    found_letter = false;
                    found_number = false;
                    res_string += '-';
                    m = 0;
                    n++;
                } else {
                    std::cout << "INVALID" << '\n';
                    return 0;
                }
            }
        }
        
    }
    if (*(res_string.end() - 1) == '-') {
            res_string.pop_back();
    }
    std::cout << res_string << '\n';
}