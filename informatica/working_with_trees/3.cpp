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

tree *Min(tree *tr){
    if(!tr->left) return tr; //нет левого ребенка
    else return Min(tr->left); //идем по левой ветке до конца
}

tree *Max(tree *tr){
    if(!tr->right) return tr; //нет правого ребенка
    else return Max(tr->right); //идем по правой ветке до конца
}

tree *Next(tree *tr, int x){
    tree *n = findNode(tr, x);
    if (n->right){
        return Min(n->right);
    }
    tree *y = n->parent;
    while (y && n == y->right){
        n = y;
        y = y->parent;
    }
    return y;
}

tree *Prev(tree *tr, int x){
    tree *n = findNode(tr, x);
    if (n->left){
        return Max(n->left);
    }
    tree *y = n->parent;
    while(y && n == y->left){
        n = y;
        y = y->parent;
    }
    return y;
}

void Delete(tree *&tr, tree *v){
    tree *p = v->parent;
    if(!p) tr = NULL; //дерево содержит один узел
    else if (!v->left && !v->right){//если нет детей
        if(p->left == v)
            p->left = NULL;
        if (p->right == v)
            p->right = NULL;
        delete v;
    }
    else if (!v->left || !v->right) { //если только один ребенок
        if(!p) {
            if (!v->left){
                tr = v->right;
                v->parent = NULL; 
            }
            else{
                tr = v->left;
                v->parent = NULL;
            }
        }
        else{
            if(!v->left){
                if(p->left == v)
                    p->left = v->right;
                else
                    p->right = v->right;
                v->right->parent = p;
            }
            else{
                if (p->left == v)
                    p->left = v->left;
                else
                    p->right = v->left;
                v->left->parent = p;
            }
            delete v;
        }
    }
    else{//если оба ребенка
        tree *succ = Next(tr, v->inf);
        v->inf = succ->inf;
        if(succ->parent->left == succ){
            succ->parent->left = succ->right;
            if (succ->right)
                succ->right->parent = succ->parent;
        }
        else{
            succ->parent->right = succ->right;
            if(succ->right)
            succ->right->parent = succ->parent;
        }
        delete succ;
    }
}

void deleteRightNephew(tree *tr, int x) {
    tree *nodeX = findNode(tr, x);
    if (!nodeX || !nodeX->parent) return;

    tree *parent = nodeX->parent;
    tree *brother; // брат родителя (дядя)
    
    // Определяем дядю
    if (parent->left == nodeX) {
        brother = parent->right;
    } else {
        brother = parent->left;
    }
    
    // Проверяем, существует ли дядя и есть ли у него правый потомок (племянник)
    if (!brother || !brother->right) return;
    
    tree *rightNephew = brother->right;
    Delete(tr, rightNephew);
}

void inorder (tree *tr){
    if (tr){
        cout << tr->inf << " ";
        inorder(tr->left);
        inorder(tr->right);
    }
}

int main() {
    tree *tr = NULL;
    
    vector<int> num = {10, 5, 33, 28, 45, 7, 3, 9, 6, 1, 25, 30};

    for(int n : num){
        insert(tr, n);
    }

    cout << "Tree before deletion: ";
    inorder(tr);
    cout << endl;

    int x = 45;
    deleteRightNephew(tr, x);

    cout << "Tree after deletion: ";
    inorder(tr);
    cout << endl;
    
    return 0;
}