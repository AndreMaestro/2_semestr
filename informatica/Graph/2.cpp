/*Дан неориентированный граф. Удалить ребро, соединяющее вершины А и B.*/

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

void deleteEdge (const vector<vector<int>> gr, int verA, int verB){

}

int main(){
    int n, m;
    bool isDirected;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;
    cout << ("is the graph directed? 1-yes, 0-no: "); cin >> isDirected;
    
    vector<vector<int>> gr = Gr(n, m, isDirected);

    int verA, verB;
    cout << "Enter vertex A: "; cin >> verA;
    cout << "Enter vertex B: "; cin >> verB;
    cout << endl;
    
    deleteEdge(gr, verA, verB);


    return 0;
}