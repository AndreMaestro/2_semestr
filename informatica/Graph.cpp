/*Граф представлен в виде списка смежности. Реализовать обход в ширину, используя очередь, и нерекурсивный обход в глубину, используя стек.*/

#include<iostream>
#include <vector>
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

int main(){

}