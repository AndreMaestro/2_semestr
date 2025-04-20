/*Дано математическое выражение в префиксной форме. Вычислить его значение*/

#include <iostream>
#include <string>
using namespace std;

struct stack{
    int inf;
    stack *next;
};

void push (stack *&h, int x){
    stack *r = new stack;
    r -> inf = x;
    r -> next = h;
    h = r;
}

int pop (stack *&h) {
    int x = h -> inf;
    stack *p = h;
    h = h->next;
    delete p;
    return x;
}

bool isOpeator(char s){
    return s == '+' || s == '-' || s == '*' || s == '/';
}

int performOperations(char op, int a, int b) {
    switch(op){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
        default: return 0;
    }
}


 int prefixSum(const string & s){
    stack *pr = NULL;
    int i = s.length()-1;//читаем справа налево

    while(i >= 0){
        if (s[i] == ' '){
            i--;
            continue;
        }

        if(isdigit(s[i])){
            push(pr, s[i]-'0');
            i--;
        }
        else if (isOpeator(s[i])){
            int a = pop(pr);
            int b = pop(pr);
            int res = performOperations(s[i], a, b);
            push(pr, res);
            i--;
        }
        else{
            i--;
        }
    }
    return pop(pr);
}

int main() {
    string prefixExpr;
    cout << "Enter prefix exprression: ";
    getline(cin, prefixExpr);

    int result = prefixSum(prefixExpr);
    cout << "Result: " << result << endl;

    return 0;
}
