/*Дан список целых чисел. Построить дерево бинарного поиска. Определить высоту дерева.*/

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

void inorder (tree *tr){
    if (tr){
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

int height(tree *tr){
    if (!tr) return 0;
    int leftH = height(tr->left);
    int rightH = height(tr->right);
    return max(leftH, rightH);
}

int main() {
    tree *tr = NULL;
    
    vector<int> num = {10, 5, 11, 15, 3, 7, 12, 20};

    for(int n : num){
        insert(tr, n);
    }

    inorder(tr);
    cout << endl;

    int treeheight = height(tr);
    cout << "Tree height: " << treeheight << endl;

    return 0;
}