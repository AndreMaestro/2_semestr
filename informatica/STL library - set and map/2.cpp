/*Во входном файле задан набор слов и целых чисел, разделенных пробелами. Найти все слова, встречающиеся столько же раз, сколько первое число (Первое число - в первоначальном наборе данных, а не в итоговом).*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main() {
    ifstream infile("2.txt");
    if (!infile) cout <<"Ошибка при открытии файла" << endl;
    string input;
    getline(infile, input);

    map<string, int> w;
    int fn = -1;

    istringstream iss(input);
    string word;

    while (iss >> word){
        if (isdigit(word[0])){
            if (fn == -1){
                fn = stoi(word);
            }
        }
        else{
            ++w[word];
        }
    }

    if (fn != -1){
        for(const auto& pair: w){
            if (pair.second == fn){
                cout << pair.first << " ";
            }
        }
        cout << endl;
    }
    else cout << "Не найдено ни одного слова";
    return 0;
}