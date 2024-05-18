// BST ���� ����
#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>

// �� ��� ����
bstreeNode* createNode(int k) {
    bstreeNode* newNode = (bstreeNode*)calloc(1, sizeof(bstreeNode));             // ������ ��� z ����
    newNode->key = k;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->p = NULL; // �� ����� �θ� �ʱ�ȭ
    return newNode;
}

// ���� ��ȸ : V L R
void preOrderTreeWalk(bstreeNode* x) {
    if (x != NULL) {
        printf("%d ", x->key);
        preOrderTreeWalk(x->left);
        preOrderTreeWalk(x->right);
    }
}

// ���� ��ȸ: L V R
void inOrderTreeWalk(bstreeNode* x) {
    if (x != NULL) {
        inOrderTreeWalk(x->left);
        printf("%d ", x->key);
        inOrderTreeWalk(x->right);
    }
}

// ���� ��ȸ: L R V
void postOrderTreeWalk(bstreeNode* x) {
    if (x != NULL) {
        postOrderTreeWalk(x->left);
        postOrderTreeWalk(x->right);
        printf("%d ", x->key);
    }
}

bstreeNode* treeSearch(bstreeNode* x, int k) {
    if (x == NULL || k == x->key)
        return x;
    if (k < x->key)
        return treeSearch(x->left, k);
    else
        return treeSearch(x->right, k);
}

bstreeNode* iterative_treeSearch(bstreeNode* x, int k) {
    while (x != NULL && k != x->key) {
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

bstreeNode* treeMin(bstreeNode* x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

bstreeNode* treeMax(bstreeNode* x) {
    while (x->right != NULL)
        x = x->right;
    return x;
}

// x�� ���� ��� ã�� ����
bstreeNode* treeSuccessor(bstreeNode* x) {
    if (x->right != NULL)
        return treeMin(x->right);           // ���� ��带 ������ ����Ʈ���� ���� ���� ���� ����
    bstreeNode* y = x->p;
    while (y != NULL && x == y->right) {        // x�� �θ� ��尡 NULL�� �ƴϰ�(���� ��Ʈ�� �������� �ʾҰ�), x�� ������ �ڽ� ��忴�ٸ�
        x = y;                                  // ��ĭ �� ���� �ö󰣴�.
        y = y->p;
    }
    return y;
}

// ���� Ž�� Ʈ���� ��� ����
void treeInsert(bstree* T, bstreeNode* z) {
    bstreeNode* y = NULL;      // �ʱ�ȭ(root ����� �θ� ��� = null)
    bstreeNode* x = T->root;   // x�� ������ root ������ ����

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y; // �� ����� �θ� ����

    if (y == NULL)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

bstreeNode* treeDelete(bstree* T, bstreeNode* z) {
    bstreeNode* y = NULL;                           // y�� ������ ���
    /* Determine which node to splice out: either z or z's successor */
    if (z->left == NULL || z->right == NULL)        // ������ ����� ���ʿ� �ڽ� ��尡 ���ų�, �ϳ��� �ִ� ���
        y = z;                                      // case 0 or 1(case 0: �ڽ� ��尡 �ƿ� ����, case 1: �ڽ� ��尡 �ϳ��� ����)   
    else
        y = treeSuccessor(z);                      //  case 2: ���� �ڽ� ��� ��� �����Ѵٸ�
                                                   // y�� ������ ����� ���� ���

    bstreeNode* x = NULL;     

    /* set x to non-NIL child of x, or to NIL if y has no children */
    // case 1) ���� ��常 �ִ� ���
    if (y->left != NULL)                            // y�� ���� �ڽ� ��尡 �ִٸ�
        x = y->left;                                // x�� y�� ���� �ڽ� ���
    else                                            // y�� ������ �ڽ� ��尡 �ִٸ�
        x = y->right;                               // x�� y�� ������ �ڽ� ���

    /* y is removed from tree by manipulating pointers of p[y] and x */
    if (x != NULL)                                 // case 1, 2
        x->p = y->p;                                // y�� ������ ��忡 �����ִ� ������ ��


    if (y->p == NULL)
        T->root = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;

    if (y != z)
        z->key = y->key;

    free(y);
    return z;
}