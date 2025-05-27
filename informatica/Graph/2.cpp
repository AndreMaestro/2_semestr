/*Дан неориентированный граф. Удалить ребро, соединяющее вершины А и B.*/

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

void deleteEdge (vector<vector<int>> &gr, int verA, int verB){
    auto itA = find(gr[verA].begin(), gr[verA].end(), verB);
    if (itA != gr[verA].end()){
        gr[verA].erase(itA);
    }

    auto itB = find(gr[verB].begin(), gr[verB].end(), verA);
    if (itB != gr[verB].end()){
        gr[verB].erase(itB);
    }
}

void printGr(const vector<vector<int>> &gr){
    for(int i = 0; i < gr.size(); i++){
        cout << "Vertex " << i << ": ";
        for (int n : gr[i]) cout << n << " ";
        cout << endl;
    }
}

int main(){
    int n, m;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;
    
    vector<vector<int>> gr = Gr(n, m);

    int verA, verB;
    cout << "Enter vertex A: "; cin >> verA;
    cout << "Enter vertex B: "; cin >> verB;
    cout << endl;
    
    cout << "Graph before edit" << endl;
    printGr(gr);
    cout << endl;

    deleteEdge(gr, verA, verB);
    cout << "Graph after edit" << endl;
    printGr(gr);
    cout << endl;

    return 0;
}