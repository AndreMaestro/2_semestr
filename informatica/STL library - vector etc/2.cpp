/*Дана последовательность целых чисел. Вывести данные в обратном порядке. Заменить числа, попадающие в интервал [𝑎, 𝑏] числом 𝑋. Отсортировать элементы. Вставить новый элемент в отсортированную последовательность (Оптимальным способом. Вставить в конец и потом опять отсортировать - не оптимально). Удалить все повторяющиеся элементы.*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, d, a, b, x, s;
    cout << "Введите n: "; cin >> n;

    /*---------*/
    vector<int> v;
    for(int i = 0; i < n; i++){
        cin >> d;
        v.push_back(d);
    }

    /*---------*/
    vector<int> v2 = v;
    for(int i = 0; i < n; i++){
        if (v.empty()) return 0;
        else{
            cout << v2.back() << " ";
            v2.pop_back();
        }
    }
    cout << endl;

    /*---------*/
    vector<int> v3 = v;
    cout << "Введите a: "; cin >> a;
    cout << "Введите b: "; cin >> b;
    cout << "Введите x: "; cin >> x;
    auto it = v3.cbegin();
    for(int i = 0; i < n; i++){
        if (v3[i] >= a && v3[i] <= b){
            v3.erase(it + i);
            v3.insert(it + i, x);
        } 
    }
    for(vector<int>::iterator it = v3.begin(); it != v3.end(); it++){
        cout << *it << " ";
    }
    cout << "\n";

    /*---------*/
    cout <<"Введите s: "; cin >> s;
    vector<int> v4 = v;
    sort(v4.begin(), v4.end());
    auto iter = lower_bound(v4.begin(), v4.end(), s);
    v4.insert(iter, s);

    for(vector<int>::iterator it = v4.begin(); it != v4.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
    
    auto iter1 = unique(v4.begin(), v4.end());
    v4.erase(iter1, v4.end());
    for(vector<int>::iterator it = v4.begin(); it != v4.end(); it++){
        cout << *it << " ";
    }
}