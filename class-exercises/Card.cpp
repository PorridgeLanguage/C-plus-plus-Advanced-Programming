#include <bits/stdc++.h>

int nums[1001];

int main() {
  int n, k;
  std::cin >> n >> k;
  int res_x = INT32_MIN;
  for (int i = 0; i < n; i++) {
    std::cin >> nums[i];
    res_x = std::max(res_x, nums[i]);
  }

  for (int i = 0; i < n; i++) {
    int cur_pos = i;
    int x_temp = nums[i];
    int count = 1;
    int j = i - 2;
    bool is_valid = true;
    while (j >= 0 && j < i) {
      if (count == k) {
        break;
      }
      if (nums[j] <= nums[i] && is_valid) {
        count++;
        is_valid = false;
      }
      if (is_valid) {
        j--;
      } else {
        j -= 2;
      }
      is_valid = true;
    }
    int m = i + 2;
    is_valid = true;
    while (m < n && m > i) {
      if (count == k) {
        break;
      }
      if (nums[m] <= nums[i] && is_valid) {
        count++;
        is_valid = false;
      }
      if (is_valid) {
        m++;
      } else {
        m += 2;
      }
      is_valid = true;
    }
    if (count == k) {
      res_x = std::min(res_x, x_temp);
    }
  }
  std::cout << res_x << "\n";
}