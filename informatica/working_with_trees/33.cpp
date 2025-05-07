#include <iostream>
#include <vector>
using namespace std;

struct tree {
    int inf;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x) {
    tree *n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}

void insert(tree *&tr, int x) {
    tree *n = node(x);
    if (!tr) tr = n;
    else {
        tree *y = tr;
        while (y) {
            if (n->inf > y->inf) {
                if (y->right) y = y->right;
                else {
                    n->parent = y;
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) {
                if (y->left) y = y->left;
                else {
                    n->parent = y;
                    y->left = n;
                    break;
                }
            }
        }
    }
}

tree *findNode(tree *tr, int x) {
    if (!tr) return NULL;
    if (tr->inf == x) return tr;
    if (x < tr->inf) return findNode(tr->left, x);
    else return findNode(tr->right, x);
}

void deleteRightNephew(tree *tr, int x) {
    tree *nodeX = findNode(tr, x);
    if (!nodeX || !nodeX->parent) return;

    tree *parent = nodeX->parent;
    tree *brother = (parent->left == nodeX) ? parent->right : parent->left;
    
    if (brother && brother->right) {
        tree *rightNephew = brother->right;
        tree *leftChild = rightNephew->left;
        tree *rightChild = rightNephew->right;
        
        brother->right = leftChild;
        if (leftChild) leftChild->parent = brother;
        
        if (rightChild) {
            tree *tmp = leftChild;
            while (tmp && tmp->right) tmp = tmp->right;
            if (tmp) {
                tmp->right = rightChild;
                rightChild->parent = tmp;
            } else {
                brother->right = rightChild;
                rightChild->parent = brother;
            }
        }
        
        cout << "Удалён правый племянник: " << rightNephew->inf << endl;
        delete rightNephew;
    }
}

void inorder(tree *tr) {
    if (tr) {
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

int main() {
    tree *tr = NULL;
    vector<int> num = {10, 5, 11, 15, 3, 7, 12, 20};

    for (int n : num) insert(tr, n);

    cout << "До удаления: ";
    inorder(tr);
    cout << endl;

    deleteRightNephew(tr, 11); // Удаляем племянников узла 11

    cout << "После удаления: ";
    inorder(tr);
    cout << endl;

    return 0;
}