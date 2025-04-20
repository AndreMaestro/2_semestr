#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void bucketSort(vector<int>& arr) { //блочная сортировка
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    int bucketCount = arr.size();
    vector<vector<int>> buckets(bucketCount);

    for (int num : arr) {
        int bucketIndex = (num - minVal) * (bucketCount - 1) / (maxVal - minVal);
        buckets[bucketIndex].push_back(num);
    }

    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end(), greater<int>());
    }

    int index = 0;
    for (auto it = buckets.rbegin(); it != buckets.rend(); ++it) {
        for (int num : *it) {
            arr[index++] = num;
        }
    }
}

void bucketSortMatrix(vector<vector<int>>& matrix) {
    for (auto& row : matrix) {
        bucketSort(row);
    }
}



int coutLines(const string& filename) {
    ifstream file(filename);
    string line;
    int n = 0;
    while (!file.eof()) {
        getline(file, line);
        n++;
    }
    return n;
}

vector<vector<int>> Matrixfromfile(const string& filename) {
    ifstream file(filename);
    int n = coutLines(filename);

    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> matrix[i][j];
        }
    }

    file.close();
    return matrix;
}

void PrintToFile(const string& filename, const vector<vector<int>>& matrix) {
    ofstream file(filename);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
}

int main() {
    string filename("input.txt");
    string output("output.txt");
    vector<vector<int>> matrix = Matrixfromfile(filename);

    bucketSortMatrix(matrix);

    PrintToFile(output, matrix);
    return 0;
}