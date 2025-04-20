#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <math.h>
using namespace std;

ifstream in("data.txt");
ofstream out ("output.txt");

struct date {
    int dd, mm, yy;
};

struct people {
    string Surname;
    string Job;
    date Dateofbirth;;
    int TimeJob; 
    int Salary; 
};


date Str_to_Date(string str){ //перевод из строки в дату
    date x;
    string temp = str.substr(0, 2);
    x.dd = atoi(temp.c_str());
    temp = str.substr(3, 2);
    x.mm = atoi(temp.c_str());
    temp = str.substr(6, 4);
    x.yy = atoi(temp.c_str());
    return x;
}


vector<people> inFile(){ //ввод из файла
    vector<people> x;
    people temp;
    while(in.peek() != EOF){
        in >> temp.Surname;
        in >> temp.Job;
        string tmp;
        in >> tmp;
        temp.Dateofbirth = Str_to_Date(tmp);
        in >> temp.TimeJob;
        in >> temp.Salary;

        x.push_back(temp);
    }
    return x;
}


void print(people x){ //вывод в файл
    out << setw(15) << left << x.Surname; 
    out << setw(25) << left << x.Job;
    if (x.Dateofbirth.dd < 10) out << left << '0' << x.Dateofbirth.dd << '.';
    else out << left << x.Dateofbirth.dd << '.';
    if (x.Dateofbirth.mm < 10) out << left << '0' << x.Dateofbirth.mm << '.';
    else out << left << x.Dateofbirth.mm << '.';
    out << left << setw(8) << x.Dateofbirth.yy;
    out << left << setw(5) << x.TimeJob;
    out << left << setw(10) << x.Salary << endl;
}


/*-----------------------------------------------------------------------------------------*/
/*3 задание*/

void porazrad_sort_LSD(vector<people> &x){
    int n = x.size();
    int p = 10; //основание системы счисления
    int k = 0;//максимальное кол-во разрядов
    //поиск максимального количества разрядов
    for (const auto i : x){
        int temp = i.Salary;
        int temp_k = 0;
        
        while (temp != 0){
            temp /= 10;
            ++temp_k;
        }
        k = max(k, temp_k);
    }

    vector<vector<people>> workers(p);

    for(int i = 0; i < k; ++i) {
        for(int j = 0; j < n; ++j){
            workers[(x[j].Salary / (int)pow(p, i)) % p].push_back(x[j]);
        }

        for(int j = 0, q = 0; j < p; ++j){
            for(const auto &z : workers[j]){
                x[q++] = z;
            }
            workers[j].clear();
        }

    }
}
/*-----------------------------------------------------------------------------------------*/

/*9 задание*/

bool sr9 (people a, people b) {
    if (a.Dateofbirth.yy < b.Dateofbirth.yy) return true;
    if (a.Dateofbirth.yy == b.Dateofbirth.yy && a.TimeJob < b.TimeJob) return true;
    return false;
}
void rascheska_sort(vector<people> &x){
    int gap = x.size()/1.247;
    while(gap >= 1){
        if (gap < 1) gap = 1;
        for (int j = 0; j < x.size()-gap; j++){
            if (sr9(x[j + gap], x[j])){
                swap(x[j], x[j + gap]);
            }
        }
        gap /= 1.247; 
    }
}
/*-----------------------------------------------------------------------------------------*/
/*14 задание*/

bool sr14 (people a, people b){
    if (a.Salary < b.Salary) return true;
    if (a.Salary == b.Salary && a.Dateofbirth.yy < b.Dateofbirth.yy) return true;
    if (a.Salary == b.Salary && a.Dateofbirth.yy == b.Dateofbirth.yy && a.TimeJob < b.TimeJob) return true;
    return false;
}


void vibor_sort(vector<people> &x){
    for(int i = 0; i < x.size(); i++){
        int min_ind = i;
        for(int j = i + 1; j < x.size(); j++){
            if (sr14(x[j], x[min_ind])) {
                min_ind = j;
            } 
        }
        swap(x[i], x[min_ind]);
    }
}
/*-----------------------------------------------------------------------------------------*/

int main() {
    vector<people> x;
    x = inFile();
    int s;
    cout << "Введите тип сортировки \n Поразрядная(По зарплате) - 1 \n Расческа(Сначала по году рождения, потом по стажу работы) - 2 \n Выбором(Сначала по зарплате, потом по году рождения, потом по стажу работы) - 3: \n"; cin >> s;

    switch(s){
        case 1: 
            porazrad_sort_LSD(x);
            break;
        case 2:
            rascheska_sort(x);
            break;
        case 3:
            vibor_sort(x);
            break;
    }
    
    for(int i = 0; i < x.size(); i++){
        print(x[i]);
    }
    return 0;
}