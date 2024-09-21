#include <iostream>

int function(int *arr, int len, int tar);

int main() {
    int len, tar;
    std::cin >> len;

    int arr[len];
    for (int i = 0; i < len; i++) {
        std::cin >> arr[i];
    }
    std::cin >> tar;
    int res = function(arr, len, tar);
    std::cout << res << '\n';
}

int function(int *arr, int len, int tar) {
    int l = 0, r;
    int min_len = len;
    int res = 0;
    int sum = 0;
    for (r = 0; r < len; r++) {
        sum += arr[r];
        while (sum >= tar) {
            int cur_len = r - l + 1;
            if (cur_len < min_len) {
                min_len = cur_len;
                if (l == r) {
                    res = l;
                } else {
                    res = l + r;
                }
            }
            sum -= arr[l];
            l++;
        }
    }
    return res;
}
