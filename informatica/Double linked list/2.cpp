/*Создать двусвязный список из целых чисел. Выполнить циклический сдвиг списка так, чтобы на первом месте было первое простое число. Например, было  4 8 6 9 1 2 3 4 5 7. Стало 2 3 4 5 7 4 8 6 9 1*/

#include <iostream>
using namespace std;

bool isPrime(int n){
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; i++){
        if (n % i == 0) return false;
    }
    return true;
}

struct list{
   int inf;
   list *next;
   list *prev; 
};

void push(list *&h, list *&t, int x){
    list *p = new list;
    p->inf = x;
    p->next = NULL;
    if(!h && !t){
        p->prev = NULL;
        h = p;
    }
    else{
        t->next = p;
        p->prev = t;
    }
    t = p;
}

void del_first(list *&h){
    h = h->next;
    h ->prev = NULL;
}

list *find_prime(list *h) {
    list *p = h;
    while (p) {
        if (isPrime(p->inf)) break;
        p = p->next;
    }
    return p;
}

void print(list *&h, list *&t){
    list *p = h;
    while(p){
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

void process_list(list *&h, list *&t){
    list *p = h;
    while(p){
        if(isPrime(p->inf)){
            if (p == h) return;

            list *new_head = p;
            list *new_tail = p->prev;

            new_tail->next = NULL;
            new_head->prev = NULL;

            t->next = h;
            h->prev = t;

            h = new_head;
            t = new_tail;

            return;
        }
        p = p->next;
    }
}

int main() {
    list *h = NULL, *t = NULL;
    int n, x;

    cout << "Enter count of numbers: ";
    cin >> n;
    cout << "Enter numbers: ";
    for(int i = 0; i < n; i++){
        cin >> x;
        push(h, t, x);
    }

    cout << "Orginal list: ";
    print(h, t);
    cout << endl;

    process_list(h, t);
    cout << "Modified list: ";
    print(h, t);
    
    return 0;
}