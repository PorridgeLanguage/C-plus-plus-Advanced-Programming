#include <iostream>
#include <string>
#include <algorithm>

typedef struct Period {
    int begin;
    int end;
} period;

#define N 1005
period periods[N];

period string2period(std::string s) {
    period cur_period;
    int begin = ((s[0] - '0') * 10 + s[1] - '0') * 60 + (s[3] - '0') * 10 + s[4] - '0';
    int end = ((s[6] - '0') * 10 + s[7] - '0') * 60 + (s[9] - '0') * 10 + s[10] - '0';
    cur_period.begin = begin;
    cur_period.end = end;
    return cur_period;
}

bool my_compare(const period &a, const period &b) {
    if (a.begin != b.begin) {
        return a.begin < b.begin;
    }
    return a.end < b.end;
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string period_string;
        std::cin >> period_string;
        period cur_period = string2period(period_string);
        periods[i].begin = cur_period.begin;
        periods[i].end = cur_period.end;
    }
    std::sort(periods, periods + n, my_compare);
    int count = 0;
    int last_end = -1;
    for (int i = 0; i < n; i++) {
        if (periods[i].begin < last_end) {
            count++;
            last_end = std::min(last_end, periods[i].end);
        } else {
            last_end = periods[i].end;
        }
    }
    std::cout << count << '\n';
}