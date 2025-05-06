/*Дан список целых чисел. Построить дерево бинарного поиска. Вывести все узлы, имеющие только правого ребенка.*/

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

void printNodeWithRight(tree *tr){
    if (tr){
        printNodeWithRight(tr->left);
        if(tr->left == NULL && tr->right != NULL){
            cout << tr->inf << " ";
        }
        printNodeWithRight(tr->right);
    }
}

int main() {
    tree *tr = NULL;
    
    vector<int> num = {10, 5, 11, 15, 3, 7, 12, 20};

    for(int n : num){
        insert(tr, n);
    }

    cout << "Node with only right child" << endl;
    printNodeWithRight(tr);
    cout << endl;

    
    return 0;
}