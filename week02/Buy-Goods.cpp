//
// Created by 35915 on 24-10-12.
//
#include<iostream>
#include<string>

#define GOODS_NUM 1000005
typedef struct {
    std::string command;
    int id;
    int buying_price;
} LOG;
LOG logs[GOODS_NUM];
int max_prices[GOODS_NUM];

int main() {
    int n, m;
    std::cin >> n; // 商品数量
    std::cin >> m; // 日志条数
    for (int i = 0; i < m; i++) {
        std::cin >> logs[i].command;
        std::cin >> logs[i].id;
        std::cin >> logs[i].buying_price;
    }
    long long sum = 0;
    for (int i = m - 1; i >= 0; i--) {
        std::string command = logs[i].command;
        int id = logs[i].id;
        int buying_price = logs[i].buying_price;
        if (buying_price > max_prices[id]) {
            max_prices[id] = buying_price;
        }
        if (command == "buy") {
            sum += max_prices[id] - buying_price;
        }
    }
    std::cout << sum << '\n';
}
/*
3 8
update 1 100
buy 1 150
update 1 200
buy 2 200
update 1 300
update 2 150
update 3 400
buy 3 500
 */
