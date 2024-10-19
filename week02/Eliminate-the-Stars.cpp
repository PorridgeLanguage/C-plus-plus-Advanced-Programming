#include <iostream>
#include <vector>
#include <queue>

int n, m, color;
int map[2000][2000];
bool visited[2000][2000];

void fall_down();
void clear_star(int i, int j);
void print();

int main() {  
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> map[i][j];
        }
    }

    int x, y;
    std::cin >> x >> y;
    color = map[x - 1][y - 1];
    
    // 清除星星
    clear_star(x - 1, y - 1);
    
    // 处理掉落
    fall_down();
    
    // 输出结果
    print();
    return 0;
}

void clear_star(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m || visited[i][j] || map[i][j] != color) 
        return;

    visited[i][j] = true; // 标记为已访问
    map[i][j] = 0; // 消除星星

    // 递归消除四个方向的星星
    clear_star(i - 1, j); // 上
    clear_star(i + 1, j); // 下
    clear_star(i, j - 1); // 左
    clear_star(i, j + 1); // 右
}

void fall_down() {
    for (int j = 0; j < m; j++) {
        int empty_row = n - 1; // 从底部开始寻找空位
        for (int i = n - 1; i >= 0; i--) {
            if (map[i][j] != 0) {
                map[empty_row--][j] = map[i][j]; // 将星星下移
            }
        }
        // 将空位填充为0
        while (empty_row >= 0) {
            map[empty_row--][j] = 0;
        }
    }
}

void print() {
    for (int i = 0; i < n; i++) {
        std::cout << map[i][0];
        for (int j = 1; j < m; j++) {
            std::cout << " " << map[i][j];
        }
        std::cout << '\n';
    }
}
