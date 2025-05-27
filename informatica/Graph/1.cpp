/*Дан ориентированный граф. Вывести на экран все вершины, не смежные с данной.*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


vector<vector<int>> Gr(int n, int m, bool isDirected){
    vector<vector<int>> Gr;
    Gr.resize(n);

    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x;
        cin >> y;

        if (x > n || y > n || x < 0 || y < 0) continue;

        if(isDirected){
            Gr[x].push_back(y);
        }
        else{
            Gr[x].push_back(y);
            Gr[y].push_back(x);
        }
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
    bool isDirected;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;
    cout << ("is the graph directed? 1-yes, 0-no: "); cin >> isDirected;
    
    vector<vector<int>> gr = Gr(n, m, isDirected);

    int ver;
    cout << "Enter a vertex to find non-adjacent vertices for it: "; cin >> ver;

    printNoAdjVer(gr, ver);
    cout << endl;

    return 0;
}