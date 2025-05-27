/*Дан неориентированный граф. Выяснить, является ли граф связным.*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


vector<vector<int>> Gr(int n, int m){
    vector<vector<int>> Gr;
    Gr.resize(n);

    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x;
        cin >> y;

        if (x > n || y > n || x < 0 || y < 0) continue;

        Gr[x].push_back(y);
        Gr[y].push_back(x);
    }

    for (int i = 0; i < n; i++){
        sort(Gr[i].begin(), Gr[i].end());
        (Gr[i].erase(unique(Gr[i].begin(), Gr[i].end()), Gr[i].end()));
    }

    return Gr;
}

vector<bool> visited;
void dfs(const vector<vector<int>> gr, int v){
    visited[v] = true;
    for(int r : gr[v]){
        if(!visited[r]) dfs(gr, r);
    }
}

bool isConnect(const vector<vector<int>> &gr){
    int n = gr.size();
    visited.assign(n, false);
    dfs(gr, 0);

    for(bool v : visited){
        if (!v) return false;
    }
    return true;
}

int main(){
    int n, m;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;
    
    vector<vector<int>> gr = Gr(n, m);

    if(isConnect(gr)) cout << "The graph is connected";
    else cout << "The graph is not connected";
    
    return 0;
}