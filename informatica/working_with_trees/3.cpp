/*Дан список целых чисел. Построить дерево бинарного поиска. Дан узел Х. Если существуют "племянники", то удалить правого из них.*/

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
tree *findNode(tree *tr, int x){
    if(!tr) return NULL;
    if (tr->inf == x) return tr;
    if (x < tr->inf) return findNode(tr->left, x);
    else return findNode(tr->right, x);
}

void deleteRightNephew(tree *tr, int x){
    tree *nodeX = findNode(tr, x);

    //проверка левого ребенка узла X
    if(nodeX->left){
        if(nodeX->left->right){
            tree *rightNephew = nodeX->left->right;
            tree *leftchild = rightNephew->left;
            tree *rightchild = rightNephew->right;
            nodeX->left->right = leftchild;
            if (leftchild) leftchild->parent = nodeX->left;

            if(rightchild) {
                tree *tmp = leftchild;
                while(tmp && tmp->right) tmp = tmp->right;
                if(tmp){
                    tmp->right = rightchild;
                    rightchild->parent = tmp;
                }
            }

            cout << "Правый племянник узла " << x << " через левого ребёнка: " << rightNephew->inf << ". DELETE" << endl;
            delete rightNephew;
        }
    }
    
    //проверка правого ребенка X
    if(nodeX->right){
        if(nodeX->right->right){
            tree *rightNephew = nodeX->right->right;
            tree *leftchild = rightNephew->left;
            tree *rightchild = rightNephew->right;
            nodeX->right->right = leftchild;
            if(leftchild) leftchild->parent = nodeX->right;

            if(rightchild){
                tree *tmp = leftchild;
                while(tmp && tmp->right) tmp = tmp->right;
                if(tmp) {
                    tmp->right = rightchild;
                    rightchild ->parent = tmp;
                } 
            }

            cout << "Правый племянник узла " << x << " через правого ребёнка: " << rightNephew->inf << ". DELETE" << endl;
            delete rightNephew;
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

int main() {
    tree *tr = NULL;
    
    vector<int> num = {10, 5, 11, 15, 3, 7, 12, 20};

    for(int n : num){
        insert(tr, n);
    }

    cout << "Tree before deletion: ";
    inorder(tr);
    cout << endl;

    int x = 10;
    deleteRightNephew(tr, x);

    cout << "Tree after deletion: ";
    inorder(tr);
    cout << endl;
    
    return 0;
}