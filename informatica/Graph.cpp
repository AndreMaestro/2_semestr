/*Граф представлен в виде списка смежности. Реализовать обход в ширину, используя очередь, и нерекурсивный обход в глубину, используя стек.*/

#include<iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

struct queue{
    int inf;
    queue *next;
};

void Qpush(queue *&h, queue *&t, int x){
    queue *r = new queue;
    r -> inf = x;
    r -> next = NULL;
    if(!h && !t){
        h = t = r;
    } 
    else{
        t -> next = r;
        t = r;
    }
}

int Qpop (queue *&h, queue *&t){
    queue *r = h;
    int i = h->inf;
    h = h->next;
    if(!h){
        t = NULL;
    }
    delete r;
    return i;
}

void BFS(const vector<vector<int>> &gr, int N, int x){
    queue *h = NULL, *t = NULL;
    vector<int> A(N, 0);
    A[x] = 1;
    Qpush(h, t, x);
    /*cout << x << " ";*/
    while(h){
        int cur = Qpop(h, t);
        cout << cur << " ";

        for(int i = 0; i < gr[cur].size(); i++){
            int y = gr[cur][i];
            if(A[y] == 0){
                A[y] = 1;
                Qpush(h, t, y);
            }
        }
    }

    for(int i = 0; i < N; i++){
        if (A[i] == 0){
            BFS(gr, N, i);
        }
    }
}

/*-------------------------------------------------------------*/
struct stack{
    int inf;
    stack *next;
};

void Spush(stack *&h, int x){
    stack *r = new stack;
    r -> inf = x;
    r -> next = h;
    h = r;
}

int Spop(stack *&h){
    int x = h->inf;
    stack *p = h;
    h = h->next;
    delete p;
    return x;
}

void DFS(const vector<vector<int>> &gr, int N, int x){
    stack *h = NULL;
    vector<int> A (N, 0);
    A[x] = 1;
    Spush(h, x);
    cout << x << " ";
    
    while(h){
        int cur = h->inf;
        bool fl = false;
        for(int i = 0; i < gr[cur].size(); i++){
            int y = gr[cur][i];
            if(A[y] == 0){
                Spush(h, y);
                A[y] = 1;
                cout<< y << " ";
                fl = true;
                break;
            }
        }

        if(!fl){
            Spop(h);
        }
    }

    for(int i = 0; i < N; i++){
        if (A[i] == 0){
            DFS(gr, N, i);
        }
    }
}

/*-------------------------------------------------------------*/

vector<vector<int>> Graph(int N){
    vector<vector<int>> gr(N);
    cout << "Enter list of adjacencies(enter one line per vertex): " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка буфера ввода

    for(int i = 0; i < N; ++i){
        cout << i << ": ";
        string line;
        getline(cin, line);
        istringstream iss(line);
        int neighbour;
        while(iss >> neighbour){
            gr[i].push_back(neighbour);
        }
    }

    return gr;
}


int main(){
    int N, x;
    cout << "Enter the number of vertices: "; cin >> N;
    vector<vector<int>> gr = Graph(N);

    cout << "Enter the starting vertex: "; cin >> x;

    cout << "DFS: ";
    DFS(gr, N, x);
    cout << endl;

    cout << "BFS: ";
    BFS(gr, N, x);
    cout << endl;

    return 0;
}