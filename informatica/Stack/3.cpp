/*Создать очередь, содержащую целые числа. После всех чисел, равных максимальному числу, вставить последний нечетный элемент. Например, было  2 8 2 1 6 8 8 1 2 2 8 2 1. Стало  2 8 1 2 1 6 8 1 8 1 1 2 2 8 1 2 1 */

#include <iostream>
using namespace std;

struct queue{
    int inf;
    queue *next;
};

void push(queue *&h, queue *&t, int x){
    queue *r = new queue;
    r ->inf = x;
    r->next = NULL;
    if(!h && !t){
        h = t = r;
    }
    else {
        t ->next = r;
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


int findMax (queue *&h){
    if (!h) return 0;

    int maxval = h -> inf;
    queue *current = h -> next;
    while (current) {
        if (current -> inf > maxval){
            maxval = current->inf;
        }
        current = current->next;
    }
    return maxval;
}

int findLastOdd(queue *&h){
    int lastOdd = 0;
    queue *current = h;
    while(current){
        if(current->inf %2 != 0){
            lastOdd = current->inf;
        }
        current = current->next;
    }
    return lastOdd;
}

void reverse(queue *&h, queue *&t) {
    queue *prev = NULL;
    queue *current = h;
    queue *next = NULL;
    
    while (current) {
        next = current->next; 
        current->next = prev; 
        prev = current; 
        current = next; 
    }
    
    
    t = h;  
    h = prev; 
}


void insertAfterMax(queue *&h, queue *&t, int maxval, int oddval){
    if (!h) return;
    
    queue *tmphead = NULL, *tmptail = NULL;

    while(h) {
        int val = pop(h, t);
        push (tmphead, tmptail, val);

        if (val == maxval) {
            push(tmphead, tmptail, oddval);
        }
    }

    while (tmphead){
        push(h, t, pop(tmphead, tmptail));
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
    
    int num[] = {2,8,2,1,6,8,8,1,2,2,8,2,1};
    int n = sizeof(num)/sizeof(num[0]);

    for(int i = 0; i < n; i++){
        push(head, tail, num[i]);
    }

    cout << "Исходная очередь: ";
    printQueue(head);

    int maxval = findMax(head);
    cout << "Максимальный элемент: " << maxval << endl;

    int lastOdd = findLastOdd(head);
    cout << "Последний нечетный элемент: " << lastOdd << endl;

    insertAfterMax(head, tail, maxval, lastOdd);

    cout << "Результат: ";
    printQueue(head);

    while(head) {
        pop(head, tail);
    }

    return 0;
}