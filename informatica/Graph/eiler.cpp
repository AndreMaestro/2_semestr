/*Дан неориентированный граф. Выяснить, является ли граф связным.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
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

bool checkEilerPath(const vector<vector<int>> &gr){
    int c = 0;
    for(int i = 0; i < gr.size(); i++){
        if (gr[i].size() % 2 != 0) c++;
    }

    if (c > 2) return false;
    return true;
}

int main(){
    int n, m;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;
    
    vector<vector<int>> gr = Gr(n, m);
    return 0;
}