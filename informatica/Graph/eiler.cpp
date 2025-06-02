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

vector<int> findEilerPath(vector<vector<int>> &gr){
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
            else return;
        } 
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
    if (v1 == -1){
        for(int i = 0; i+1 < n; i++){
            if ((res[i] == v1 && res[i+1] == v2) || (res[i] == v2 && res[i+1] == v1)){
                vector<int> newP;
                newP.insert(newP.end(), res.begin() + i + 1, res.end());
                newP.insert(newP.end(), res.begin() + 1, res.end() + i + 1);
                res = newP;
                break;
            }
        }
    }

    //Проверяем, все ли рёбра использованы
    for(int d : degrees){
        if (d != 0) return;
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