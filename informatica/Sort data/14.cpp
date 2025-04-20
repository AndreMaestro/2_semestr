#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
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

bool operator < (people a, people b){
    if (a.Salary < b.Salary) return true;
    if (a.Salary == b.Salary && a.Dateofbirth.yy < b.Dateofbirth.yy) return true;
    if (a.Salary == b.Salary && a.Dateofbirth.yy == b.Dateofbirth.yy && a.TimeJob < b.TimeJob) return true;
    return false;
}

void vibor_sort(vector<people> &x){
    for(int i = 0; i < x.size(); i++){
        int min_ind = i;
        for(int j = i + 1; j < x.size(); j++){
            if (x[j] < x[min_ind]) {
                min_ind = j;
            } 
        }
        swap(x[i], x[min_ind]);
    }
}


int main() {
    vector<people> x;
    x = inFile();
    vibor_sort(x);
    for(int i = 0; i < x.size(); i++){
        print(x[i]);
    }
    return 0;
}