//
// Created by 35915 on 24-10-13.
//
#include<iostream>
#include<algorithm>

#define N 1005
typedef struct {
    int start;
    int end;
    bool visited;
} POS;
POS pos[N];

bool my_compare(const POS &a, const POS &b) {
    if (a.start != b.start) {
        return a.start < b.start;
    }
    return a.end < b.end;
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> pos[i].start;
        std::cin >> pos[i].end;
        pos[i].visited = false;
    }
    std::sort(pos, pos + n, my_compare);
    int time = 0;
    int cur_pos = 0;
    int cur_index = 0;
    while (cur_index < n) {
        cur_pos = cur_pos + 27;
        if (cur_pos >= pos[cur_index].start) {
            if (cur_pos > pos[cur_index].end) {
                cur_pos = pos[cur_index].end;
            }
            pos[cur_index].visited = true;
            int i = cur_index;
            while (i < n && cur_pos >= pos[i].start) {
                if (!pos[i].visited && pos[i].end <= cur_pos) {
                    pos[i].visited = true;
                    cur_pos = pos[i].end;
                }
                i++;
            }
            while (cur_index < n && pos[cur_index].start <= cur_pos) {
                pos[cur_index].visited = true;
                cur_index++;
            }
        }
        time += 1;
    }
    std::cout << time << "T\n";
    return 0;
}
