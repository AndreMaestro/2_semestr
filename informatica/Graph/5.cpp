/*Дан ориентированный граф. Найти все сильно связные компоненты графа.*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> gr;
vector<vector<int>> grT;
vector<bool> used;
vector<int> order;
vector<int> path;

void dfs1(int x) {
    used[x] = true;
    for (int n : gr[x]) {
        if (!used[n]) {
            dfs1(n);
        }
    }
    order.push_back(x);
}

void dfs2(int x) {
    used[x] = true;
    path.push_back(x);
    for (int n : grT[x]) {
        if (!used[n]) {
            dfs2(n);
        }
    }
}

int main() {
    int n, m;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;

    gr.resize(n);
    grT.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;

        if (x >= n || y >= n || x < 0 || y < 0) continue;

        gr[x].push_back(y);
        grT[y].push_back(x);
    }

    // Первый проход DFS (заполнение order)
    used.assign(n, false);
    order.clear();
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    reverse(order.begin(), order.end());

    // Второй проход DFS (поиск SCC)
    used.assign(n, false);
    cout << "\nStrongly Connected Components:\n";
    for (int v : order) {
        if (!used[v]) {
            path.clear();
            dfs2(v);
            for (int vertex : path) {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }

    return 0;
}