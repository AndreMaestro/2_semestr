/*Дан ориентированный граф. Найти все сильно связные компоненты графа.*/

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


int main(){
    int n, m;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;
    
    vector<vector<int>> gr = Gr(n, m);
  
    return 0;
}