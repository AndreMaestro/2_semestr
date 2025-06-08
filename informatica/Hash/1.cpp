/*Открытое хэширование: Метод умножения по дню рождения*/

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
    date date_of_bithday;
    int exp;
    int pay;
};

struct list{
    worker inf;
    list *prev;
    list *next;
};

struct List {
    list *h;
    list *t;
};

void push(list *&h, list *&t, worker x){
    list *r = new list;
    r->inf = x;
    r->next = nullptr;
    if(!h && !t){
        r->prev = nullptr;
        h = r;
    }
    else{
        t->next = r;
        r->prev = t;
    }
    t = r;
}

void print_worker(worker x){
    string i = x.date_of_bithday.day / 10 == 0 ? "0" : "";
    string i1 = x.date_of_bithday.month / 10 == 0 ? "0" : "";
    cout << x.surname << ", " << x.post << ", " << i << x.date_of_bithday.day << "." << i1 << x.date_of_bithday.month << "." << x.date_of_bithday.year << ", " << x.exp << ", " << x.pay << endl;
}

void print(list *&h, list *&t){
    list *p = h;
    while(p){
        print_worker(p->inf);
        p = p->next;
    }
    cout << endl;
}

vector<list*> find(list *&h, list *&t, int x){
    vector<list*> res;
    list *p = h;
    while(p){
        if (p->inf.date_of_bithday.day == x) res.push_back(p);
        p = p->next;
    }
    return res;
}

void delete_node(list *&h, list *&t,list *&r){
    if (r == h && r == t){
        h = t = nullptr;
    }
    else if (r == h){
        h = h->next;
        h->prev = nullptr;
    }
    else if (r == t){
        t = t->prev;
        t->next = nullptr;
    }
    else {
        r->prev->next = r->next;
        r->next->prev = r->prev;
    }
    delete r;
}


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
    human.date_of_bithday.day = stoi(str.substr(i, i1-i));
    i = i1 + 1; i1 = str.find_first_of(".", i);
    human.date_of_bithday.month = stoi(str.substr(i, i1-i));
    i = i1 + 1; i1 = str.find_first_of(".", i);
    human.date_of_bithday.year = stoi(str.substr(i, i1-i));
    k = k1 + 2; k1 = str.find_first_of(",", k);
    human.exp = stoi(str.substr(k, k1 - k));
    k = k1 + 2; k1 = str.find_first_of(",", k);
    human.pay = stoi(str.substr(k, k1 - k));

    return human;
}

vector<List> createHashTab (vector<worker> A, int M){
    vector<List> hashTable(M);
    for (int i = 0; i < A.size(); i++){
        int k = h(A[i].date_of_bithday.day, M);
        push(hashTable[k].h, hashTable[k].t, A[i]);
    }
    return hashTable;
}

void printHashTable (vector<List> hashTable){
    for (int i = 0; i < hashTable.size(); i++){
        cout << i << " : \n";
        print(hashTable[i].h, hashTable[i].t);
    }
}

void findHash(vector<List> hashTable, int x){
    int k = h(x, hashTable.size());
    vector<list*> temp = find(hashTable[k].h, hashTable[k].t, x);
    if (temp.size() == 0) cout << "Not found\n";
    else{
        for(int i = 0; i < temp.size(); i++){
            print_worker(temp[i]->inf);
        }
    }
}

void delHash(vector<List> &hashTable, int x){
    int k = h(x, hashTable.size());
    vector<list*> temp = find(hashTable[k].h, hashTable[k].t, x);
    for (int i = 0; i < temp.size(); i++){
        delete_node(hashTable[k].h, hashTable[k].t, temp[i]);
    }
}

void enterHash(vector<List> &hashTable){
    string x;
    getline(cin, x);
    worker tmp = str_to_worker(x);
    int k = h(tmp.date_of_bithday.day, hashTable.size());
    push(hashTable[k].h, hashTable[k].t, tmp);
}

int main() {
    ifstream in("data.txt");
    vector<worker> A(20);
    int M = 16;
    string str;
    for(int i = 0; i < 20; i++){
        getline(cin, str);
        A[i] = str_to_worker(str);
    }
    vector<List> hashTable = createHashTab(A, M);
    printHashTable(hashTable);
    cout << "\n-------------------------------\n";
    enterHash(hashTable);
    cout << "\n-------------------------------\n";
    printHashTable(hashTable);
    cout << "\n-------------------------------\n";
    findHash(hashTable, 29);
    cout << "\n-------------------------------\n";
    delHash(hashTable, 29);
    printHashTable(hashTable);

}

/*Semenov Designer 15.02.1982 21 85000*/