/*Дан набор целых чисел. Удалить все минимальные числа.*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, x;
    cout << "Введите n: "; cin >> n;
    vector<int> c;
    for(int i = 0; i < n; i++){
        cin >> x;
        c.push_back(x);
    }

    int Min = *min_element(c.begin(), c.end());

    c.erase(remove(c.begin(), c.end(), Min), c.end());

    for(vector<int>::iterator it = c.begin(); it != c.end(); it++){
        cout << *it << " ";
    }
}