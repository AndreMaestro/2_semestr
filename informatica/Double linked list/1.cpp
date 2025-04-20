/*Создать двусвязный список, содержащий целые числа. Перед всеми числами, равными последнему числу, вставить минимальный элемент. Например, было 8 2 1 6 8 8 1 2 2 8 2. Стало 8 1 2 1 6 8 8 1 1 2 1 2 8 1 2*/

#include <iostream>
#include <climits>
using namespace std;

struct list {
    int inf;
    list *next;
    list *prev;
};

void push(list *&h, list *&t, int x){
    list *r = new list;
    r ->inf = x;
    r ->next = NULL;
    if (!h && !t) {
        r -> prev = NULL;
        h = r;
    } 
    else {
        t -> next = r;
        r -> prev = t;
    }
    t = r;
}


void print(list *h, list *t){
    list *p = h;
    while (p){
        cout << p->inf << " ";
        p = p->next;
    }
}

int find_min(list *h) {
    int min_val = INT_MAX;
    list *p = h;
    while (p) {
        if (p->inf < min_val) {
            min_val = p->inf;
        }
        p = p->next;
    }
    return min_val;
}

void insert_before (list *&h, list *&t, list *r, int y){
    list *p = new list;
    p -> inf = y;
    if(r == h){
        p->prev = NULL;
        p->next = r;
        r->prev = p;
        h = p;
    }
    else{
        r->prev->next = p;
        p->prev = r->prev;
        p->next = r;
        r->prev = p;
    }
}

void process_list(list *&h, list *&t){
    if(!h && !t) return;
    
    int last_val = t->inf;
    int min_val = find_min(h);
    
    list *current = h;
    while(current){
        if(current->inf == last_val){
            insert_before(h, t, current, min_val);
        }
        current = current ->next;
    }
}

int main(){
    list *h = NULL, *t = NULL;
    int n, x;

    cout << "Enter numbers" << endl;
    cin >> n;
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