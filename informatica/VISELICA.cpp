#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdlib> // Для rand() и srand()
#include <ctime>   // Для time()

using namespace std;


int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(0));

    vector<vector<string>> man = {
        {"   -----|    ",
        "  |     |    ",
        "  0     |    ",
        "        |    ",
        "        |    ",
        " ------------"},
        {"   -----|    ",
        "  |     |    ",
        "  0     |    ",
        "  |     |    ",
        "        |    ",
        " ------------"},
        {"   -----|    ",
        "  |     |    ",
        "  0     |    ",
        " /|     |    ",
        "        |    ",
        " ------------"},
        {"   -----|    ",
        "  |     |    ",
        "  0     |    ",
        " /|/    |    ",
        "        |    ",
        " ------------"},
        {"   -----|    ",
        "  |     |    ",
        "  0     |    ",
        " /|/    |    ",
        " //     |    ",
        " ------------"}
    };

    vector<string> words = {
        "KEYBOARD", "COMPUTER", "INFORMATICS",
        "PROGRAMMING", "UNIVERSITY", "MESSENGER",
        "PROCESSOR", "SMARTPHONE", "BUILDING",
        "COMPETITIONS", "INTERNET", "SUPERMARKET"
    };

    int ind = rand() % words.size();
    string val = words[ind];
    //cout << val;
    /*заполняем вектор буквами слова*/
    vector<char> w;
    for (int i = 0; i < val.size(); i++) {
        w.push_back(val[i]);
    }
    /*
    for (auto c : w) {
        cout << c << " ";
    }
    */
    cout << endl;
    string res;
    for (int i = 0; i < w.size(); i++) {
        res += "_";
    }
    cout << res << endl;

    vector<string> alphabet{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    /*for (auto c : alphabet) cout << c << " ";*/
    cout << endl;

    int cnt = 0, maxcnt = 5;

    while (cnt != maxcnt) {
        string q;
        cout << "Если вы знаете слово, введите 'a', иначе 'b': "; cin >> q;
        if (q == "a") {
            string r;
            cout << "Введите слово: "; cin >> r;
            if (r == val) {
                cout << "WIN!!!";
                return 0;
            }
            else {
                cout << "GAME OVER" << endl;
                cout << "Загаданное слово: " << val;
                return 0;
            }
        }

        else if (q == "b") {
            cout << res << endl;
            for (auto c : alphabet) cout << c << " ";
            string bukv;
            vector<size_t> indixes;
            cout << "Введите букву: "; cin >> bukv;
            if (val.find(bukv) != val.npos) {
                for (int i = 0; i < alphabet.size(); i++) {
                    if (alphabet[i] == bukv) {
                        alphabet[i] = "*";
                    }
                }
                for (size_t i = 0; i < val.length(); i++) {
                    if (val.substr(i, 1) == bukv) {
                        indixes.push_back(i);
                    }
                }
                for (int i = 0; i < indixes.size(); i++) {
                    res.replace(indixes[i], 1, bukv);
                }
                if (res == val) {
                    cout << "WIN!!!";
                    return 0;
                }
                cout << res << endl;
            }
            else {
                cnt += 1;
                for (int i = 0; i < alphabet.size(); i++) {
                    if (alphabet[i] == bukv) {
                        alphabet[i] = "*";
                    }
                }
                if (cnt != 5) cout << "Try again" << endl;
                for (auto line : man[cnt - 1]) {
                    cout << line << "\n";
                }
                if (res != val && cnt == 5) {
                    cout << "GAME OVER" << endl;
                    cout << "Загаданное слово: " << val;
                    return 0;
                }
            }
        }

        if (res == val) {
            cout << "WIN!!!";
            return 0;
        }
    }

    return 0;
}