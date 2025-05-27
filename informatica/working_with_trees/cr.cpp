/*Даны числа: 5, 4, 8, 1, 9, 2, 7, 6, 0, 3. Создать дерево бинарного поиска (написать функцию).
Вывести дерево. Написать функцию для обратного обхода и вывести результат*/

#include <iostream>
#include <string>
#include<vector>
using namespace std;

struct tree {
    int inf;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x){
    tree *n = new tree;
    n ->inf = x;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(tree *&tr, int x){
    tree *n = node(x);
    if(!tr) tr = n; //если дерево пустое - корень
    else{
        tree *y = tr;
        while(y){
            if(n->inf > y->inf) //правая ветка
                if(y ->right)
                    y = y->right;
                else{
                    n->parent = y;
                    y->right = n;
                    break;
                }
            else if (n->inf < y->inf) //левая ветка
                if (y->left)
                    y = y->left;
                else{
                    n->parent = y;
                    y->left = n;
                    break;
                }
        }
    } 
}

void postorder (tree *tr){
    if (tr){
        postorder(tr->left);
        postorder(tr->right);
        cout << tr->inf << " ";
    }
}

int main() {
    tree *tr = NULL;
    
    vector<int> num = {5, 4, 8, 1, 9, 2, 7, 6, 0, 3};

    for(int n : num){
        insert(tr, n);
    }

    postorder(tr);
    cout << endl;
    return 0;
}