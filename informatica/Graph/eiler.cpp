/*Дан неориентированный граф. Вывести Эйлеров путь или Эйлеров цикл, если он существует.*/

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
    int start = -1;
    
    // Находим первую вершину с ненулевой степенью
    for(int i = 0; i < n; i++) {
        if(!gr[i].empty()) {
            start = i;
            break;
        }
    }
    
    if(start == -1) return true; // граф без ребер
    
    dfs(gr, start);

    // Проверяем только вершины с ребрами
    for(int i = 0; i < n; i++) {
        if(!gr[i].empty() && !visited[i]) {
            return false;
        }
    }
    return true;
}

vector<int> findEilerPath(vector<vector<int>> gr){
    int n = gr.size();
    vector<int> degrees(n);
    vector<int> res;
    stack<int> st;

    //Определяем степени всех вершин
    for(int i = 0; i < n; i++){
        degrees[i] = gr[i].size();
    }


    //Находим вершины с нечетными степенями
    int v1 = -1, v2 = -1;
    for(int i = 0; i < n; i++){
        if(degrees[i] % 2 != 0){
            if(v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            else return{};
        } 
    }

    // Проверяем условия существования Эйлерова пути/цикла
    if(!(v1 == -1 || v2 == -1)) {
        if(!isConnect(gr)) return {};
    } else {
        if(!isConnect(gr)) return {};
    }

    //Если есть вершины с нечётными степенями, добавляем ребро
    bool addedEdge = false;
    if(v1 != -1){
        gr[v1].push_back(v2);
        gr[v2].push_back(v1);
        degrees[v1]++;
        degrees[v2]++;
        addedEdge = true;
    }

    //Выбираем начальную вершину
    int start = (v1 != -1)? v1:0;
    st.push(start);

    //Основной алгоритм
    while(!st.empty()){
        int v = st.top();

        if (degrees[v] != 0){
            int u = gr[v].back();
            gr[v].pop_back();

            auto it = find(gr[u].begin(), gr[u].end(), v);
            if(it != gr[u].end()){
                gr[u].erase(it);
            }

            degrees[v]--;
            degrees[u]--;

            st.push(u);
        }

        else{
            res.push_back(v);
            st.pop();
        }
    }

    //Если добавляли ребро, корректируем путь
    if (addedEdge){
        for(int i = 0; i+1 < res.size(); i++){
            if ((res[i] == v1 && res[i+1] == v2) || (res[i] == v2 && res[i+1] == v1)){
                vector<int> newP;
                newP.insert(newP.end(), res.begin() + i + 1, res.end());
                newP.insert(newP.end(), res.begin() + 1, res.begin() + i + 1);
                res = newP;
                break;
            }
        }
    }

    //Проверяем, все ли рёбра использованы
    for(int d : degrees){
        if (d != 0 && d != 2) return{};
    }
    return res;
}

int main(){
    int n, m;

    cout << "Enter the number of vertices (n): "; cin >> n;
    cout << "Enter the number of edges (m): "; cin >> m;
    
    vector<vector<int>> gr = Gr(n, m);

    vector<int> Path = findEilerPath(gr);

    if (Path.empty()) cout << " Euler’s path does not exist";
    else{
        if(Path.front() == Path.back()) cout << "Euler`s cycle: ";
        else cout << "Euler`s path: ";
        
        for(int v : Path){
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}