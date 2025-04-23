/*Дана шахматная доска. Вывести кратчайший путь конем от клетки А до клетки В. Должны быть введены две клетки в виде, например, А2 и Е6. Путь должен быть выведен в виде списка клеток А2 В4 С6 D8 E6*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <climits>
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
        r = r;
    }
}