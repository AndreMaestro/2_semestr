/*Создать стек, содержащий целые числа. Удалить все простые числа. Порядок следования в результате должен совпадать с порядком следования ввода. Например, было 1 2 3 4 5 6 7 8 9. Стало 1 4 6 8 9*/

#include <iostream>
using namespace std;


bool isPrime(int n){
    if (n <= 1) return false;
    for(int i = 2; (i*i) <= n; i++){
        if (n % i == 0) return false;
    }
    return true;
}

struct stack {
    int inf;
    stack *next;
};

void push (stack *&h, int x){
    stack *r = new stack;
     r -> inf = x;
     r -> next = h;
     h = r;
}

int pop(stack *& h) {
    int x = h -> inf;
    stack *p = h;
    h = h -> next;
    delete p;
    return x;
}

void reverse(stack *& h){
    stack *head1 = NULL;
    while(h) {
        push(head1, pop(h));
    }
    h = head1;
}

stack * removePrimeNum (stack *&h){
    stack *tmp = NULL, *res = NULL;

    while (h != NULL){
        int num = pop(h);
        push(tmp, num);
    }

    while(tmp != NULL){
        int num = pop(tmp);
        if(!isPrime(num)){
            push(res, num);
        }
        push(h, num);
    }
    reverse(res);
    return res;
}

void printStack(stack *& h) {
    stack* tmp = h;
    while(tmp != NULL){
        cout << tmp -> inf << " ";
        tmp = tmp -> next;
    }
    cout << endl;
}

int main() {
    stack *original = NULL;

    push(original, 1);
    push(original, 2);
    push(original, 3);
    push(original, 4);
    push(original, 5);
    push(original, 6);
    push(original, 7);
    push(original, 8);
    push(original, 9);

    cout << "Исходный стек: ";
    printStack(original);

    stack * result = removePrimeNum(original);

    cout << "После удаления простых чисел: ";
    printStack(result);
}