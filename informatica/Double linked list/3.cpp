#include <iostream>
using namespace std;

struct list {
    int inf;
    list *next;
    list *prev;
};

// Добавление элемента в конец списка
void push(list *&h, list *&t, int x) {
    list *r = new list;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {
        r->prev = NULL;
        h = r;
    } 
    else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

// Печать списка
void print(list *h, list *t) {
    list *p = h;
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

// Получение последнего узла списка
list* getTail(list* cur) {
    while (cur && cur->next)
        cur = cur->next;
    return cur;
}

// Разделение списка для быстрой сортировки
list* partition(list* l, list* h, list* &newHead, list* &newTail) {
    list* pivot = h;
    list* prev = NULL, *cur = l, *tail = pivot;
    
    while (cur != pivot) {
        if (cur->inf < pivot->inf) {
            if (newHead == NULL)
                newHead = cur;
            prev = cur;
            cur = cur->next;
        } 
        else {
            if (prev)
                prev->next = cur->next;
            list* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            cur->prev = tail;
            tail = cur;
            cur = tmp;
        }
    }
    
    if (newHead == NULL)
        newHead = pivot;
    
    newTail = tail;
    return pivot;
}

// Рекурсивная реализация быстрой сортировки
list* quickSortRecur(list* l, list* h) {
    if (!l || l == h)
        return l;
    
    list *newHead = NULL, *newTail = NULL;
    list* pivot = partition(l, h, newHead, newTail);
    
    if (newHead != pivot) {
        list* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        
        newHead = quickSortRecur(newHead, tmp);
        
        tmp = getTail(newHead);
        tmp->next = pivot;
        pivot->prev = tmp;
    }
    
    pivot->next = quickSortRecur(pivot->next, newTail);
    if (pivot->next)
        pivot->next->prev = pivot;
    
    return newHead;
}

// Основная функция быстрой сортировки
void quickSort(list* &head, list* &tail) {
    head = quickSortRecur(head, tail);
    tail = getTail(head);
}

// Обработка списка (сортировка)
void process_list(list *&h, list *&t) {
    quickSort(h, t);
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