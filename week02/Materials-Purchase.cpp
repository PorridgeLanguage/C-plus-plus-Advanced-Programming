//
// Created by 35915 on 24-10-15.
//
#include<iostream>

#define N 100005
int fund[N];
int n;

bool can_meet_target(int price, double k, double target) {
    double sum = 0;
    double remaining = 0;
    for (int i = 0; i < n; i++) {
        sum += (int)(fund[i] / price);
        remaining += fund[i] % price;
    }
    sum += remaining / ((double)price - k);
    return sum >= target;
}

int main() {

    std::cin >> n;
    double target, k;
    std::cin >> target >> k;
    for (int i = 0; i < n; i++) {
        std::cin >> fund[i];
    }
    int low = 1, high = 100000;
    int result = -1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if (can_meet_target(mid, k, target)) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    std::cout << result << '\n';
    return 0;
}