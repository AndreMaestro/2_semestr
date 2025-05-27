/*Дан ориентированный граф. Вывести на экран все вершины, не смежные с данной.*/

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
        
    }

    for (int i = 0; i < n; i++){
        sort(Gr[i].begin(), Gr[i].end());
        (Gr[i].erase(unique(Gr[i].begin(), Gr[i].end()), Gr[i].end()));
    }

    return Gr;
}

void printNoAdjVer(const vector<vector<int>> &gr, int ver){
    int n = gr.size();

    vector<bool> adj(n, false);

    for (int v : gr[ver]){
        adj[v] = true;
    }

    for (int i = 0; i < n; i++){
        for(int v: gr[i]){
            if (v == ver){
                adj[i] = true;
                break;
            }
        }
    }

    cout << "Vertices not adjacent to " << ver << ": ";
    bool f = false;
    for (int i = 0; i < n; i++){
        if (i != ver && !adj[i]){
            cout << i << " ";
            f = true;
        }
    }

    if (!f){
        cout << "All vertices are adjacent to " << ver;
    }
}

int main(){
    int n, m;
    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;

    vector<vector<int>> gr = Gr(n, m);

    int ver;
    cout << "Enter a vertex to find non-adjacent vertices for it: "; cin >> ver;

    printNoAdjVer(gr, ver);
    cout << endl;

    return 0;
}