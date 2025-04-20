/*Дан текст, состоящий из предложений, разделенных знаками препинания из набора «.?!». Предложения в свою очередь состоят из слов, отделенных друг от друга пробелами. Найти слова (без учета регистра), которые встречаются только в повествовательных предложениях.*/

/*Hello world! How are you? I am fine. And what are you doing? I am programming hello world.*/
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    set<string> pov;
    set<string> vopr;
    set<string> vosk;
    string razd = "?!.";
    string razd2 = "?!. ";
    string text;
    getline(cin, text);
    size_t pos = 0;
    size_t k = text.find_first_of(razd, pos);
    while (k != string::npos) {
        string temp = text.substr(pos,k - pos + 1);
        size_t pos1 = 0;
        size_t k1 = temp.find_first_of(razd2, pos1);
        while (k1 != string::npos) {
            string word = temp.substr(pos1,k1 - pos1);
            for (int i = 0; i < word.size(); i++) {
                if (isupper(word[i])) {
                    word[i] = tolower(word[i]);
                }
            }
            switch (text[k]) {
                case '?': vopr.insert(word); break;
                case '.': pov.insert(word); break;
                case '!': vosk.insert(word); break;
            };
            pos1 = k1 + 1;
            k1 = temp.find_first_of(razd2, pos1);
        }
        pos = k + 2;
        k = text.find_first_of(razd, pos);
    }
    for (set<string>::iterator it = pov.begin(); it != pov.end(); it++) {
        if (vopr.count(*it) == 0 && vosk.count(*it) == 0){
            cout << *it << " ";
        }
    }
}