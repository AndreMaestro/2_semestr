/*Создать двусвязный список. После всех элементов, содержащих данную цифру, вставить новый элемент. Дополнительный список использовать нельзя.*/

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

void insert_after(list *&h, list *&t, list *r, int y) {
    list *p = new list;
    p->inf = y;
    if (r == t) {
        p->next = NULL;
        p->prev = r;
        r->next = p;
        t = p;
    } else {
        p->next = r->next;
        p->prev = r;
        r->next->prev = p;
        r->next = p;
    }
}

void process_list(list *&h, list *&t, int g, int new_value) {
    if (!h && !t) return;
    
    list *current = h;
    while (current) {
        if (current->inf == g) {
            insert_after(h, t, current, new_value);
            current = current->next; 
        }
        current = current->next;
    }
}

int main() {
    list *h = NULL, *t = NULL;
    int n, x;
    int num, newN;

    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        push(h, t, x);
    }

    cout << "Original list: ";
    print(h, t);
    cout << endl;

    cout << "Enter the number after which to insert: ";
    cin >> num;
    cout << "Enter the new number to insert: ";
    cin >> newN;

    process_list(h, t, num, newN);
    
    cout << "Modified list: ";
    print(h, t);

    return 0;
}