/*Закрытое хэширование: Основная — линейное хеширование, вспомогательная — метод умножения по году*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

struct date{
    int day;
    int month;
    int year;
};

struct worker{
    string surname;
    string post;
    date date_of_birthday;
    int exp;
    int pay;
};


int h(int x, int M){
    double A = (sqrt(5) - 1) / 2; //золотое сечение
    return int(M * (x * A - int(x * A)));//хэш
}

worker str_to_worker(string str){
    worker human;
    size_t k = 0; size_t k1 = str.find_first_of(",");
    human.surname = str.substr(k, k1 - k);
    k = k1 + 2; k1 = str.find_first_of(",", k);
    human.post = str.substr(k, k1 - k);
    k = k1 + 2; k1 = str.find_first_of(",", k);
    size_t i = k; size_t i1 = str.find_first_of(".", k);
    human.date_of_birthday.day = stoi(str.substr(i, i1-i));
    i = i1 + 1; i1 = str.find_first_of(".", i);
    human.date_of_birthday.month = stoi(str.substr(i, i1-i));
    i = i1 + 1; i1 = str.find_first_of(".", i);
    human.date_of_birthday.year = stoi(str.substr(i, i1-i));
    k = k1 + 2; k1 = str.find_first_of(",", k);
    human.exp = stoi(str.substr(k, k1 - k));
    k = k1 + 2; k1 = str.find_first_of(",", k);
    human.pay = stoi(str.substr(k, k1 - k));

    return human;
}

vector<worker> createHashTab (vector<worker> A, int M){
    vector<worker> hashTable(M);
    for(int i = 0; i < A.size(); i++){
        int k = h(A[i].date_of_birthday.year, M);
        int j = 0; 
        for(int t = 0; t < M; t++){
            int p = (k + j) % M;
            if(hashTable[p].date_of_birthday.year == 0){
                hashTable[p] = A[i];
                break;
            }
            else j++;
        }
    }
    return hashTable;
}

void print_worker(worker x){
    string i = x.date_of_birthday.day / 10 == 0 ? "0" : "";
    string i1 = x.date_of_birthday.month / 10 == 0 ? "0" : "";
    cout << x.surname << ", " << x.post << ", " << i << x.date_of_birthday.day << "." << i1 << x.date_of_birthday.month << "." << x.date_of_birthday.year << ", " << x.exp << ", " << x.pay << endl;
}

void printHashTable (vector<worker> hashTable){
    for(int i = 0; i < hashTable.size(); i++){
        cout << i << " : ";
        if (hashTable[i].date_of_birthday.year) print_worker(hashTable[i]);
        else cout << '\n';
    }
}

void findHash(vector<worker> hashTable, int x){
    int k = h(x, hashTable.size());
    bool f = false;
    for (int t = 0; t < hashTable.size(); t++){
        int p = (k + t) % hashTable.size();
        if(hashTable[p].date_of_birthday.year == x){
            print_worker(hashTable[p]);
            f = true;
        }
    }
    if (!f) cout << "Not found\n";
}

void enterHash(vector<worker> &hashTable){
    string x;
    getline(cin, x);
    worker tmp = str_to_worker(x);
    int k = h(tmp.date_of_birthday.year, hashTable.size());
    int j = 0;
    for(int t = 0; t < hashTable.size(); t++){
        int p = (k + j) % hashTable.size();
        if(hashTable[p].date_of_birthday.year == 0){
            hashTable[p] = tmp;
            break;
        }
        else j++;
    }    
}

int main() {
    ifstream in("data.txt");
    vector<worker> A(20);
    int M = 32;
    string str;
    for(int i = 0; i < 20; i++){
        getline(in, str);
        A[i] = str_to_worker(str);
    }
    vector<worker> hashTable = createHashTab(A, M);
    printHashTable(hashTable);
    cout << "\n-------------------------------\n";
    enterHash(hashTable);
    cout << "\n-------------------------------\n";
    printHashTable(hashTable);
    cout << "\n-------------------------------\n";
    findHash(hashTable, 1983);
}

/*Semenov, Designer, 15.02.1982, 21, 85000*/