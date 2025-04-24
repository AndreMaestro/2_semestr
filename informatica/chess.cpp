/*Дана шахматная доска. Вывести кратчайший путь конем от клетки А до клетки В. Должны быть введены две клетки в виде, например, А2 и Е6. Путь должен быть выведен в виде списка клеток А2 В4 С6 D8 E6*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <climits>
#include <algorithm>
using namespace std;

int x_step[] = {-2, -2, 2, 2, 1, 1, -1, -1};
int y_step[] = {1, -1, 1, -1, 2, -2, 2, -2};

struct queue{
    pair<int, int> inf;
    queue* next;
};

void push(queue *&h, queue *&t, pair<int, int> x){
    queue *r = new queue;
    r->inf = x;
    r->next = NULL;
    if(!h && !t){
        h = t = r;
    }
    else{
        t->next = r;
        t = r;
    }
}

pair<int, int> pop(queue*& h, queue *& t){
    queue *r = h;
    pair<int, int> i = h->inf;
    h = h->next;
    if (!h){
        t = NULL;
    }
    delete r;
    return i;
}

bool isValid(int x, int y, int N){
    return (x >= 0 && x < N) && (y >= 0 && y < N);
}

struct node{
    int x, y, dist;
    pair<int, int> par;
    node(int x, int y, int dist = 0, pair<int, int> p = {-1,-1}): x(x), y(y), dist(dist), par(p){}
    bool operator <(const node &d){
        return (x < d.x || (x == d.x && y < d.y));
    }
};

vector<pair<int, int>> ShortestPath(int N, pair<int, int> begin, pair<int, int> end){
    set<pair<int, int>> visit;
    queue *h = NULL, *t = NULL;
    vector<pair<int, int>> parent(N*N, {-1,-1});
    //начало обхода в ширину(BFS)
    push(h, t, begin);
    visit.insert(begin);

    while(h){
        pair<int, int> current = pop(h, t);
        if(current == end) break;

        int x = current.first;
        int y = current.second;
        for(int i = 0; i < 8; i++){
            int x1 = x + x_step[i];
            int y1 = y + y_step[i];
            if(isValid(x1, y1, N) && visit.count({x1, y1}) == 0){
                push(h, t, {x1, y1});
                visit.insert({x1, y1});
                parent[x1*N + y1] = current;
            }
        }
    }

    vector<pair<int, int>> Way;
    pair<int, int> cur = end;
    while(end != begin){
        if(cur.first == -1 || parent[cur.first*N + cur.second] == make_pair(-1,-1)) return {};

        Way.push_back(cur);
        cur = parent[cur.first*N + cur.second];
    }
    Way.push_back(begin);
    reverse(Way.begin(), Way.end());
    return Way;
}
