/*Создать очередь из целых чисел. Выполнить циклический сдвиг очереди так, чтобы на первом месте было первое составное число. Например, было  2 3 5 4 8 6 9 1 4 5 7. Стало 4 8 6 9 1 4 5 7 2 3 5*/

#include <iostream>
using namespace std;

bool isComposite(int n){
    if (n <= 1) return false;
    if (n == 2 || n == 3) return false;
    if (n % 2 == 0) return true;
    for(int i = 3; i*i <= n; i += 2) {
        if(n % i == 0) return true;
    }
    return false;
}

struct queue {
    int inf;
    queue *next;
};

void push (queue *&h, queue *&t, int x){
    queue *r = new queue;
    r ->inf = x;
    r ->next = NULL;
    if(!h && !t) {
        h = t = r;
    }
    else {
        t -> next = r;
        t = r;
    }
}

int pop (queue *&h, queue *&t) {
    queue *r = h;
    int i = h -> inf;
    h = h -> next;
    if(!h){
        t = NULL;
    }
    delete r;
    return i;
}

void rotateToFirstComposite (queue *&h, queue *&t) {
    if (!h) return;

    queue *current = h;
    while (current && !isComposite(current->inf)) {
        current = current -> next;
    }

    if (!current) return;

    while (h != current) {
        int val = pop(h, t);
        push (h, t, val);
    }
}

void printQueue (queue *h){
    queue *current = h;
    while (current) {
        cout << current->inf << " ";
        current = current -> next;
    }
    cout << endl;
}

int main() {
    queue *head = NULL, *tail = NULL;

    int num[] = {2,3,5,4,8,6,9,1,4,5,7};
    int n = sizeof(num)/sizeof(num[0]);

    for(int i = 0; i < n; i++){
        push(head, tail, num[i]);
    }


    cout << "Исходная очередь: ";
    printQueue(head);

    rotateToFirstComposite(head, tail);

    cout << "После сдвига: ";
    printQueue(head);
    
    
    return 0;
}