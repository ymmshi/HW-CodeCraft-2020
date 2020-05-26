#include <bits/stdc++.h>
#include <cstdio>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>

using namespace std;
using namespace chrono;
#define MAX_VERTEX_SIZE 280000
unordered_map<int,int> vertex_hash;
array<array<int, 32>, MAX_VERTEX_SIZE> G{}, GInv{};
array<array<int, 2>, MAX_VERTEX_SIZE> vertex_raw;
array<string, MAX_VERTEX_SIZE> id2str;

auto *res7 = new array<int, 7>[3000000];
auto *res6 = new array<int, 6>[2000000];
auto *res5 = new array<int, 5>[1000000];
auto *res4 = new array<int, 4>[1000000];
auto *res3 = new array<int, 3>[1000000];
int cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
int vertex_num = 0;

void load_data(const string &path) {
    int fd = open(path.c_str(), O_RDONLY);
    auto len = lseek(fd, 0, SEEK_END);
    char *buf = (char *) mmap(nullptr, len, PROT_READ, MAP_PRIVATE, fd, 0);
    int p = 0;
    for (off_t i = 0, j = 0, a = 0; j < len; j++) {
        if (buf[j] == ',') {
            a = a <= i ? j + 1 : a;
        } else if (buf[j] == '\n') {
            vertex_raw[p++] = {atoi(buf + i), atoi(buf + a)};
            i = j + 1;
        }
    }
    stable_sort(vertex_raw.begin(), vertex_raw.begin() + p, greater<array<int, 2>>());
    for (int i = 0; i < p; ++i) {
        if (vertex_hash.count(vertex_raw[i][0])) {
            id2str[++vertex_num] = to_string(vertex_raw[i][0]) + ',';
            vertex_hash[vertex_raw[i][0]] = vertex_num;
        }
    }
    ++vertex_num;
    for (int i = 0; i < p; ++i) {
        if (vertex_hash.count(vertex_raw[i][1])) {
            int &hash_to = vertex_hash[vertex_raw[i][1]];
            int &hash_from = vertex_hash[vertex_raw[i][0]];
            G[hash_from][++G[hash_from][0]] = hash_to;
            GInv[hash_to][++GInv[hash_to][0]] = hash_from;
        }
    }
}

void find_circle() {
    vector<bool> no_visited(vertex_num, true);
    vector<int> reachable(vertex_num, INT_MAX);
    auto *path_idx = new array<int, 2>[vertex_num];
    auto *idx_path = new int[vertex_num];
    auto *path = new array<array<int, 2>, 128>[8000];
    for (int i = 0; i < vertex_num; ++i) {
        if (!G[i][0] || !GInv[i][0] || G[i][1] > i) continue;
        int idx = 0;
        auto &ms = GInv[i];
        for (auto m = ms.begin() + 1; m <= ms.begin() + ms[0] && *m < i; ++m) {
            auto &ns = GInv[*m];
            for (auto n = ns.begin() + 1; n <= ns.begin() + ns[0] && *n < i; ++n) {
                auto &js = GInv[*n];
                for (auto j = js.begin() + 1; j <= js.begin() + js[0] && *j < i; ++j) {
                    if (*m != *j) {
                        if (reachable[*j] != i) {
                            reachable[*j] = i;
                            idx_path[idx] = *j;
                            path_idx[*j] = {0, idx++};
                        }
                        path[path_idx[*j][1]][path_idx[*j][0]++] = {*n, *m};
                    }
                }
            }
        }
        for (int k = 0; k < idx; k++) {
            if (path_idx[idx_path[k]][0] > 1)
                sort(path[k].begin(), path[k].begin() + path_idx[idx_path[k]][0]);
        }

        for (auto a = G[i].begin() + 1; a <= G[i].begin() + G[i][0] && *a < i; ++a) {
            if (!G[*a][0] || G[*a][1] > i) continue;
            if (reachable[*a] == i) {
                for (int l = 0; l < path_idx[*a][0]; ++l) {
                    res4[cnt4++] = {i, *a, path[path_idx[*a][1]][l][0], path[path_idx[*a][1]][l][1]};
                }
            }
            no_visited[*a] = false;
            for (auto b = G[*a].begin() + 1;
                 b <= G[*a].begin() + G[*a][0] && *b < i; ++b) {
                if (!G[*b][0] || G[*b][1] > i) continue;
                if (reachable[*b] == i) {
                    for (int l = 0; l < path_idx[*b][0]; ++l) {
                        if (no_visited[path[path_idx[*b][1]][l][0]] && no_visited[path[path_idx[*b][1]][l][1]]) {
                            res5[cnt5++] = {i, *a, *b, path[path_idx[*b][1]][l][0], path[path_idx[*b][1]][l][1]};
                        }
                    }
                }
                auto c = G[*b].begin() + 1;
                no_visited[*b] = false;
                for (; c <= G[*b].begin() + G[*b][0] && *c < i; ++c) {
                    if (no_visited[*c]) {
                        no_visited[*c] = false;
                        if (reachable[*c] == i) {
                            auto &len_c = path_idx[*c][0];
                            for (int l = 0; l < len_c; ++l) {
                                if (no_visited[path[path_idx[*c][1]][l][0]] &&
                                    no_visited[path[path_idx[*c][1]][l][1]]) {
                                    res6[cnt6++] = {i, *a, *b, *c, path[path_idx[*c][1]][l][0],
                                                    path[path_idx[*c][1]][l][1]};

                                }
                            }
                        }
                        for (auto j = G[*c].begin() + 1; j <= G[*c].begin() + G[*c][0]; ++j) {
                            if (reachable[*j] == i && no_visited[*j]) {
                                for (int l = 0; l < path_idx[*j][0]; ++l) {
                                    auto n = path[path_idx[*j][1]][l][0];
                                    auto m = path[path_idx[*j][1]][l][1];
                                    if (no_visited[n] && no_visited[m]) {
                                        res7[cnt7++] = {i, *a, *b, *c, *j, n, m};
                                    }
                                }
                            }
                        }
                        no_visited[*c] = true;
                    }
                }
                if (c <= G[*b].begin() + G[*b][0] && *c == i) {
                    res3[cnt3++] = {i, *a, *b};
                }
                no_visited[*b] = true;
            }
            no_visited[*a] = true;
        }
    }
}

void save_result(const string &save_path) {
    int cnt = cnt3 + cnt4 + cnt5 + cnt6 + cnt7;
    string sz = to_string(cnt);
    int fd = open(save_path.c_str(), O_RDWR | O_CREAT, 0666);
    char *ans = new char[300000000];
    int p = sz.size();
    memcpy(ans, sz.c_str(), p);
    ans[p] = '\n';
    for (int i = cnt3 - 1; i >= 0; i--) {
        for (auto &j:res3[i]) {
            memcpy(ans + p + 1, id2str[j].c_str(), id2str[j].size());
            p += id2str[j].size();
        }
        ans[p] = '\n';
    }
    for (int i = cnt4 - 1; i >= 0; i--) {
        for (auto &j:res4[i]) {
            memcpy(ans + p + 1, id2str[j].c_str(), id2str[j].size());
            p += id2str[j].size();
        }
        ans[p] = '\n';
    }
    for (int i = cnt5 - 1; i >= 0; i--) {
        for (auto &j:res5[i]) {
            memcpy(ans + p + 1, id2str[j].c_str(), id2str[j].size());
            p += id2str[j].size();
        }
        ans[p] = '\n';
    }
    for (int i = cnt6 - 1; i >= 0; i--) {
        for (auto &j:res6[i]) {
            memcpy(ans + p + 1, id2str[j].c_str(), id2str[j].size());
            p += id2str[j].size();
        }
        ans[p] = '\n';
    }
    for (int i = cnt7 - 1; i >= 0; i--) {
        for (auto &j:res7[i]) {
            memcpy(ans + p + 1, id2str[j].c_str(), id2str[j].size());
            p += id2str[j].size();
        }
        ans[p] = '\n';
    }
    write(fd, ans, p);
    close(fd);
}


int main() {
    load_data("/data/test_data.txt");
    find_circle();
    save_result("/projects/student/result.txt");
    return 0;
}
