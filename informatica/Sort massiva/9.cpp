#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


void rascheska_sort_ost(vector<int>& arr){
    int n = arr.size();
    int gap = n/1.247;
    while(gap >= 1){
        if(gap < 1) gap = 1;
    
        for(int j = 0; j < n-gap; j++){
            if (arr[j] > arr[j+gap]) swap(arr[j], arr[j+gap]);
        }
        gap /= 1.247;   
    }
}
void rascheska_sort_kazd_tr(vector<int>& arr){
    int n = arr.size();
    int gap = n/1.247;
    while(gap >= 1){
        if(gap < 1) gap = 1;
    
        for(int j = 0; j < n-gap; j++){
            if (arr[j] < arr[j+gap]) swap(arr[j], arr[j+gap]);
        }
        gap /= 1.247;   
    } 
}

void rascheska_sort(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int k = 0;
    for (int column = 0; column < n; column++) {
        vector<int> arr;
        for (const auto& row : matrix) {
            arr.push_back(row[column]);
        }
        if ((k+1) % 3 == 0) {
            rascheska_sort_kazd_tr(arr);
        } 
        else {
            rascheska_sort_ost(arr);
        }
        

        for (int i = 0; i < n; i++) {
            matrix[i][column] = arr[i];
        }
        k++;
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
    rascheska_sort(matrix);
    PrintToFile(output, matrix);
    return 0;
}