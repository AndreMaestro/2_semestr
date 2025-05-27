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

vector<bool> used; 
vector<int> path;

void DFS(const vector<vector<int>>& Gr, int x) {
    used[x] = true;
    path.push_back(x);
    
    for (int i = 0; i < Gr[x].size(); i++) {
        int neighbor = Gr[x][i];
        if (!used[neighbor]) {
            DFS(Gr, neighbor);
        }
    }
}

int main(){
    int n, m;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;

    vector<vector<int>> gr = Gr(n, m);

    used.resize(n, false);
    
    int startVertex;
    cout << endl;
    cout << "Enter starting vertex for DFS (0-" << n-1 << "): "; 
    cin >> startVertex;
    
    if (startVertex < 0 || startVertex >= n) {
        cout << "Invalid starting vertex!" << endl;
        return 1;
    }

    DFS(gr, startVertex);

    cout << endl;
    cout << "DFS traversal order: ";
    for (int vertex : path) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}