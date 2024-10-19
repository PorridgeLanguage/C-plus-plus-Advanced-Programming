#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>
#include <cstring>

const int MAX_M = 100;
const int MAX_N = 6;
const int INF = INT_MAX;

int dist[MAX_M][MAX_M]; // distant matrix
int n;                  // order nums
int m;                  // spots nums
int dp[(1 << MAX_N) + 1][(1 << MAX_N) + 1][MAX_M];
typedef struct ORDER{
    int rest;           // restaurant
    int cust;           // customer
}order;
order orders[MAX_N];
int calculate(int maskFetch, int maskSend, int last) {
    // all FINISHED
    if (maskFetch == (1 << n) - 1 && maskSend == (1 << n) - 1) {
        return 0;
    }

    if (dp[maskFetch][maskSend][last] != -1) {
        return dp[maskFetch][maskSend][last];
    }

    int ans = INF;

    for (int i = 0; i < n; i++) {
        if ((maskFetch & (1 << i)) && !(maskSend & (1 << i))) {
            int time = dist[last][orders[i].cust];
            int newMaskFetch = maskSend | (1 << i);
            int nextTime = time + calculate(maskFetch, newMaskFetch, orders[i].cust);
            ans = std::min(ans, nextTime);
        }
        if (!(maskFetch & (1 << i))) {
            int time = dist[last][orders[i].rest];
            int newMaskFetch = maskFetch | (1 << i);
            int nextTime = time + calculate(newMaskFetch, maskSend, orders[i].rest);
            ans = std::min(ans, nextTime);
        }
    }
    dp[maskFetch][maskSend][last] = ans;
    return ans;
}

int main() {
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> dist[i][j];
            if (dist[i][j] == -1) {
                dist[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int cur_rest, cur_cust;
        std::cin >> cur_rest >> cur_cust;
        orders[i].rest = cur_rest - 1;
        orders[i].cust = cur_cust - 1;
    }
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    for (auto &i: dp) {
        for (auto &j: i) {
            for (int &k: j) {
                k = -1;
            }
        }
    }
    int result = calculate(0, 0, 0);

    std::cout << result << std::endl;
    return 0;
}