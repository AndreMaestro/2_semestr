#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void sortSecondaryDiagonals(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    // Сортировка диагоналей выше побочной
    for (int d = 1; d < n; d++) {
        vector<int> diagonal;
        // Собираем элементы диагонали
        for (int i = 0, j = n - 1 - d; i <= d && j <= n - 1; i++, j++) {
            diagonal.push_back(matrix[i][j]);
        }
        // Сортируем диагональ
        bubbleSort(diagonal);
        // Записываем отсортированные элементы обратно
        int index = 0;
        for (int i = 0, j = n - 1 - d; i <= d && j <= n - 1; i++, j++) {
            matrix[i][j] = diagonal[index++];
        }
    }
    
    // Сортировка диагоналей ниже побочной
    for (int d = 1; d < n; d++) {
        vector<int> diagonal;
        // Собираем элементы диагонали
        for (int i = d, j = 0; i <= n - 1 && j <= n - 1 - d; i++, j++) {
            diagonal.push_back(matrix[i][j]);
        }
        // Сортируем диагональ
        bubbleSort(diagonal);
        // Записываем отсортированные элементы обратно
        int index = 0;
        for (int i = d, j = 0; i <= n - 1 && j <= n - 1 - d; i++, j++) {
            matrix[i][j] = diagonal[index++];
        }
    }
    
    // Сортировка самой побочной диагонали
    vector<int> mainDiagonal;
    for (int i = 0, j = n - 1; i < n; i++, j--) {
        mainDiagonal.push_back(matrix[i][j]);
    }
    bubbleSort(mainDiagonal);
    for (int i = 0, j = n - 1, k = 0; i < n; i++, j--, k++) {
        matrix[i][j] = mainDiagonal[k];
    }
}





int coutLines(const string& filename){ //количество строк в исходном файле
    ifstream file(filename);
    string line;
    int n = 0;
    while (!file.eof()){
        getline(file, line);
        n++;
    }
    return n;
}


vector<vector<int>> Matrixfromfile(const string& filename){ //создание двумерного массива
    ifstream file(filename);
    int n = coutLines(filename);

    vector<vector<int>> matrix(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n;  j++){
            file >> matrix[i][j];
        }
    }

    file.close();
    return matrix;
}


void PrintToFile(const string& filename, const vector<vector<int>>& matrix){ //вывод в файл
    ofstream file(filename);
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
}


int main(){
    string filename("input.txt");
    string output("output.txt");
    vector<vector<int>> matrix = Matrixfromfile(filename);
    sortSecondaryDiagonals(matrix);

    PrintToFile(output, matrix);
    return 0;
}