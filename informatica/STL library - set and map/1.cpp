/*Дана последовательность целых чисел. Найти все такие цифры, которые встречаются в двузначных числах, но не встречаются в трехзначных. Работать только с цифрами, которые встречаются в данной последовательности, а не со всеми цифрами от 0 до 9.*/

#include <iostream>
#include <set>
#include <cmath>
using namespace std;

int main() {
    int n, x, r, t, y;
    cout << "Введите n: "; cin >> n;
    set<int> a;
    for(int i = 0; i < n; i++){
        cin >> x;
        a.insert(x);
    }


    set<int> dv;
    set<int> tr;

    for(set<int>::iterator it = a.begin(); it != a.end(); it++){
        if ((9 < abs(*it)) && (abs(*it) < 100)){
            r = abs(*it) % 10;
            t = abs(*it) / 10;
            dv.insert(r);
            dv.insert(t);
        }
        if ((99 < abs(*it)) && (abs(*it) < 1000)){
            r = abs(*it) % 10;
            t = (abs(*it) / 10) % 10;
            y = abs(*it) / 100;
            tr.insert(r);
            tr.insert(t);
            tr.insert(y);
        }
    }

    for(set<int>::iterator it = dv.begin(); it != dv.end(); it++){
        if (tr.find(*it) == tr.end()) {
            cout << *it << " ";
        }
    }
}