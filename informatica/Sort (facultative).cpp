/*Дан набор целых чисел. Отсортировать их по возрастанию, используя Тимсорт*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void insertSort(vector<int> &a, int l, int r){
    for(int i = l+1; i <= r; i++){
        int k = a[i];
        int j = i - 1;
        while(j >= l && a[j] > k){
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = k;
    }
}

void merge(vector<int> &a, int l, int m, int r){
    int len1 = m - l + 1; 
    int len2 = r - m;
    vector<int> left(len1);
    vector<int> right(len2);
    for(int i = 0; i < len1; i++){
        left[i] = a[l+i];
    }
    for(int i = 0; i < len2; i++){
        right[i] = a[m + 1 + i];
    }

    int k = l, i = 0, j = 0;
    while(i < len1 && j < len2){
        if(left[i] <= right[j]){
            a[k++] = left[i++];
        }
        else{
            a[k++] = right[j++];
        }
    }

    while (i < len1){
        a[k++] = left[i++];
    }
    while(j < len2){
        a[k++] = right[j++];
    }
}

void timSort(vector<int> &a){
    const int n = a.size();
    const int R = 32; //размер подмассива для сортировки вставками
    
    for(int i = 0; i < n; i += R) {
        insertSort(a, i, min(i+R-1, n-1));
    }

    for(int s = R; s < n; s *= 2){
        for(int left= 0; left < n; left += 2*s){
            int m = left + s - 1;
            int right = min(left + 2*s - 1, n - 1);

            if(m < right){
                merge(a, left, m, right);
            }
        }
    }
}

int main() {
    vector<int> numbers = {34,2,10,-9,7,3,0};
    timSort(numbers);
    for(int n:numbers){
        cout << n << " ";
    } 
    return 0;
}