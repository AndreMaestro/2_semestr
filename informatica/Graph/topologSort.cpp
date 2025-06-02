/*Дан ориентированный граф. Если это возможно, реализовать топологическую сортировку*/

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
    }

    for (int i = 0; i < n; i++){
        sort(Gr[i].begin(), Gr[i].end());
        (Gr[i].erase(unique(Gr[i].begin(), Gr[i].end()), Gr[i].end()));
    }

    return Gr;
}

bool dfs(const vector<vector<int>> &gr, vector<bool> &visited, vector<bool> &inStack, int v, stack<int> &st){
    visited[v] = true;
    inStack[v] = true;

    for(int u : gr[v]){
        if (!visited[u]) {
            if(!dfs(gr, visited, inStack, u, st))
                return false;
        }
        else if (inStack[u])
            return false;
    }

    inStack[v] = false;
    st.push(v);
    return true;
}

vector<int> TopologicalSort (const vector<vector<int>> gr){
    int n = gr.size();
    vector<bool> inStack(n, false);
    vector<bool> visited(n, false);
    stack<int> st;
    bool ExistCycle = false;

    for(int i = 0; i < n; i++){
        if (!visited[i]){
            if (!dfs(gr, visited, inStack, i, st)){
                ExistCycle = true;
                return{};
            }
        }
    }

    vector<int> res;
    while(!st.empty()){
        res.push_back(st.top());
        st.pop();
    }

    return res;
}

int main(){
    int n, m;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;
    
    vector<vector<int>> gr = Gr(n, m);
    vector<int> sort = TopologicalSort(gr);
    
    for(int v : sort){
        cout << v << " ";
    }

    return 0;
}