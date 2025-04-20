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

/*bool operator < (people a, people b){
    if (a.Salary < b.Salary) return true;
    return false;
}*/

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


int main() {
    vector<people> x;
    x = inFile();
    porazrad_sort_LSD(x);
    for(int i = 0; i < x.size(); i++){
        print(x[i]);
    }
    return 0;
}