#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtreeNode* createRBTreeNode(int k, rbtree* T) {
    rbtreeNode* newNode = (rbtreeNode*)calloc(1, sizeof(rbtreeNode));
    newNode->key = k;
    newNode->left = T->nil;
    newNode->right = T->nil;
    newNode->p = T->nil;
    newNode->color = RED;
    return newNode;
}

rbtree* createRBTree() {
    rbtree* T = (rbtree*)malloc(sizeof(rbtree));
    rbtreeNode* nilNode = (rbtreeNode*)malloc(sizeof(rbtreeNode));
    nilNode->color = BLACK;
    T->nil = nilNode;
    T->root = T->nil;
    return T;
}

const char* getColor(Color color) {
    return color == RED ? "RED" : "BLACK";
}


// ��� �Լ�
#include <stdio.h>
#include "rbtree.h"

void inOrderRBTreeWalk(rbtreeNode* x, rbtree* T) {
    if (x == T->nil) return;
    inOrderRBTreeWalk(x->left, T);

    // �θ� ��� Ű �� ����
    char parentKey[20];
    if (x->p == T->nil) {
        snprintf(parentKey, sizeof(parentKey), "nil");
    }
    else {
        snprintf(parentKey, sizeof(parentKey), "%d", x->p->key);
    }

    // ���� �ڽ� ��� Ű �� ����
    char leftKey[20];
    if (x->left == T->nil) {
        snprintf(leftKey, sizeof(leftKey), "nil");
    }
    else {
        snprintf(leftKey, sizeof(leftKey), "%d", x->left->key);
    }

    // ������ �ڽ� ��� Ű �� ����
    char rightKey[20];
    if (x->right == T->nil) {
        snprintf(rightKey, sizeof(rightKey), "nil");
    }
    else {
        snprintf(rightKey, sizeof(rightKey), "%d", x->right->key);
    }

    printf("Node: %d, Color: %s, Parent: %s, LeftNode's key: %s, RightNode's key: %s \n",
        x->key, getColor(x->color), parentKey, leftKey, rightKey);

    inOrderRBTreeWalk(x->right, T);
}


// �޸� ���� �Լ�
void freeRBNode(rbtree* T, rbtreeNode* x) {
    if (x != T->nil) {
        freeRBNode(T, x->left);
        freeRBNode(T, x->right);
        free(x);
    }
}

void freeRBTree(rbtree* T) {
    freeRBNode(T, T->root);
    free(T->nil);
    free(T);
}

rbtreeNode* rbtreeSearch(rbtreeNode* x, rbtree* T, int k) {
    while (x != T->nil && k != x->key) {
        if (k < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    return x;
}

// rbtree min
rbtreeNode* rbtreeMin(rbtree *T, rbtreeNode* x) {
    while (x->left != T->nil)
        x = x->left;
    return x;
}
/*      ���� ȸ�� ����     */
void leftRotate(rbtree* T, rbtreeNode* x) {
    rbtreeNode* y = x->right;                                  // y ����: y�� x�� ������ �ڽ� ���
    x->right = y->left;                                         // y�� ���� ����Ʈ���� x�� ������ ����Ʈ���� �����.

    if (y->left != T->nil)                                         // y�� ���� �ڽ� ��尡 nil ��尡 �ƴ� ���γ����
        y->left->p = x;                                         // �θ�� x�� �����Ѵ�.

    y->p = x->p;                                                    // x�� �θ� y�� �����Ѵ�.

    if (x->p == T->nil)                                            // CASE 1. ������ x�� �θ� nil �����(����� Ʈ�� �󿡼��� ��Ʈ)
        T->root = y;                                                      // x�� ��Ʈ�� ���, y�� ���ο� ��Ʈ�� �ȴ�.
    else if (x == x->p->left)                                    // CASE 2. x�� �θ��� ���� �ڽ��� ���
        x->p->left = y;
    else                                                        // CASE 3. x�� �θ��� ������ �ڽ��� ���
        x->p->right = y;

    y->left = x;                                             // x�� y�� ���� �ڽ����� �����.
    x->p = y;                                               // x�� �θ� y�� �����Ѵ�.
}

/*      ������ ȸ�� ����     */
void rightRotate(rbtree* T, rbtreeNode* x) {
    rbtreeNode* y = x->left; 
    x->left = y->right;

    if (y->right != T->nil)
        y->right->p = x;

    y->p = x->p;

    if (x->p == T->nil)
        T->root = y;
    else if (x == x->p->right)
        x->p->right = y;
    else
        x->p->left = y;

    y->right = x;
    x->p = y;
}

/*      ���� �� Ʈ�� ���� ����    */
void RB_Insert(rbtree* T, rbtreeNode *z) {
    rbtreeNode* y = T->nil;
    rbtreeNode* x = T->root;                                        //x�� T�� ��Ʈ ��带 ����Ű�� �����Ͱ����� �����Ѵ�.

    /* ��Ʈ�������� �� �������鼭, BST ���� ����ó�� �����Ѵ�. */
    while (x != T->nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y; //z�� �θ� �����Ѵ�.
    if (y == T->nil) //CASE 1) z�� �θ� sentinel �����(��, z�� ���Ե� �ڸ��� ��Ʈ)
        T->root = z;
    else if (z->key < y->key)
        y->left = z; // CASE 2) z�� �θ��� ���� �ڽ��� ��� 
    else
        y->right = z; // CASE 3) z�� �θ��� ������ �ڽ��� ���

    z->left = T->nil;
    z->right = T->nil;
    z->color = RED; // ���ԵǴ� ����� ������ �׻� red�� ����
    RB_Insert_FixUp(T, z);
}

/*      ����-�� Ʈ�� ���� �� ���� ����        */
void RB_Insert_FixUp(rbtree* T, rbtreeNode* z) {
    rbtreeNode* y;

    while (z->p != T->nil && z->p->color == RED) {
        if (z->p == z->p->p->left) {         // �θ� ��尡 ���θ� ����� ���� �ڽ��̶��
            y = z->p->p->right;              // ���� ���� ���θ� ����� ������ �ڽ� ���
            /* CASE 1: ���� ��� ���� ������ ��� */
            if (y->color == RED) {
                z->p->color = BLACK; // �θ� ����� ������ ������ �����.
                y->color = BLACK;    // ���� ����� ���� ������ �����.
                z->p->p->color = RED; // ���θ� ����� ���� ����� �����.
                z = z->p->p;          // �� ĭ ���� �Ž��� �ö� �����Ѵ�.(Bottom-up)
            }
            /* ���� ��� ���� ���� ��� */
            else {
                if (z == z->p->right) {// CASE 2. ���� ��� ���� ���̰�, z�� ������ �ڽ��� ���
                    z = z->p;         // �θ� ��忡 ����
                    leftRotate(T, z); // ���� ȸ�� ���� ����
                }
                // CASE 3. ���� ��� ���� ���̰�, z�� ������ �ڽ��� ���
                z->p->color = BLACK; // �θ����� ������ ������ ������ش�.
                z->p->p->color = RED; // ���θ� ��� ������ ����� ������ش�.
                rightRotate(T, z->p->p); // ���������� ȸ��
            }
        }
        else {                                  // �θ� ��尡 ���θ� ����� ������ �ڽ��̶��
            y = z->p->p->left;                  // ���� ���� ���θ� ����� ���� �ڽ�
            /* CASE 1: ���� ��� ���� ������ ��� */
            if (y->color == RED) {
                z->p->color = BLACK;     // �θ� ����� ������ ������ ����
                y->color = BLACK;        // ���� ����� ������ ������ ����
                z->p->p->color = RED;    // ���θ� ����� ������ ����� ����
                z = z->p->p;             // �� ĭ ���� �Ž��� �ö� �����Ѵ�.
            }
            /* ���� ��� ���� ���� ��� */
            else {
                if (z == z->p->left) { // CASE 2. ���� ����� ���� ���̰�, z�� ���� �ڽ��� ���
                    z = z->p;         // �θ� ��忡 ����
                    rightRotate(T, z); // ������ ȸ�� ���� ����
                }
                // CASE 3. ���� ��� ���� ���̰�, z�� ������ �ڽ��� ���
                z->p->color = BLACK; // �θ����� ������ ������ ������ش�.
                z->p->p->color = RED; // ���θ� ��� ������ ����� ������ش�.
                leftRotate(T, z->p->p); // ���������� ȸ��
            }
        }
    }
    T->root->color = BLACK; // ��Ʈ ����� ������ �׻� ��
}

void RB_Transplant(rbtree* T, rbtreeNode* u, rbtreeNode* v) {
    if (u->p == T->nil) {      // ������ ��尡 root �� ���
        T->root = v;
    }
    else if (u == u->p->left) {
        u->p->left = v;
    }
    else {
        u->p->right = v;
    }
    v->p = u->p;
}

void RB_Delete(rbtree* T, rbtreeNode* z) {
    rbtreeNode* y = z;
    rbtreeNode* x;
    Color y_original_color = y->color;

    if (z->left == T->nil) {
        x = z->right;
        RB_Transplant(T, z, z->right);
    }
    else if (z->right == T->nil) {
        x = z->left;
        RB_Transplant(T, z, z->left);
    }
    else {
        y = rbtreeMin(T, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->p == z) {
             x->p = y;
        }
        else {
            RB_Transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        RB_Transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK)
        RB_Delete_FixUp(T, x);
}

/*      RBT ���� �� ���� ����    */

void RB_Delete_FixUp(rbtree* T, rbtreeNode* x) {
    while (x != T->nil && x != T->root && x->color == BLACK) {
        if (x == x->p->left) {               // ������ x�� ���� �ڽ��� ���
            rbtreeNode* w = x->p->right;   // w�� x�� ���� ����� ��������
            /* CASE 1: x�� ���� w�� ������ ��� */
            if (w->color == RED) {
                w->color = BLACK;           // ���� ����� ������ ������ �ٲ۴�.
                x->p->color = RED;          // �θ� ����� ������ ����� �ٲ۴�.
                leftRotate(T, x->p);        // �θ� ��忡 ���� ���� ȸ�� ���� ����
                w = x->p->right;            // ���ο� ������ �����Ѵ�.
            }

            /* CASE 2: x�� ���� w�� ���̰�, w�� �� �ڽ� ��嵵 ��� ���� ��� */
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;             // ���� ����� ������ ����� �ٲ۴�.
                x = x->p;                   // x�� x�� �θ� ���� �����Ѵ�.
            }
            else {
                /* CASE 3: x�� ���� w�� ���̰�, w�� ���� �ڽ� ���� ����, ������ �ڽ� ���� ���� ��� */
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;     // w�� ���� �ڽ� ��� ������ ������ �ٲ۴�.
                    w->color = RED;             // w�� ������ ����� �ٲ۴�.
                    rightRotate(T, w);          // w�� ���� ������ ȸ�� ���� ����
                    w = x->p->right;            // ���� ���� ���� x�� �θ� ����� ������ �ڽ� ��� 
                }

                /* CASE 4: x�� ���� w�� BLACK�̰� w�� ������ �ڽ��� RED�� ��� */
                w->color = x->p->color;        // ���� ��带 �θ��� ������ �ٲ۴�.
                x->p->color = BLACK;           // �θ� ��带 BLACK���� �ٲ۴�.
                w->right->color = BLACK;        // ������ ������ �ڽ��� BLACK���� �ٲ۴�.
                leftRotate(T, x->p);           // �θ� ��忡 ���� ��ȸ�� ����
                x = T->root;
            }
        }
        else {                              // ������ x�� ������ �ڽ��� ���
            rbtreeNode* w = x->p->left;    // ���� ��� w�� ���� �ڽ� ���

            /* CASE 1: x�� ���� w�� ������ ��� */
            if (w->color == RED) {
                w->color = BLACK;           // ���� ����� ������ ������ ������ش�.
                x->p->color = RED;          // �θ� ����� ������ ����� �����.
                rightRotate(T, x->p);       // �θ� ��忡 ���� ������ ȸ�� ���� ����
                w = x->p->left;             // ������ ���ο� ������ �θ� ����� ���� �ڽ� ���
            }

            /* CASE 2: x�� ���� w�� ���̰�, w�� �� �ڽ� ��嵵 ��� ���� ��� */
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->p;
            }
            else {
                /* CASE 3: x�� ���� w�� ���̰�, w�� ������ �ڽ� ���� ����, ���� �ڽ� ���� ���� ��� */
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(T, w);
                    w = x->p->left;
                }

                /* CASE 4: x�� ���� w�� ���̰�, w�� ���� �ڽ��� ������ ��� */
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rightRotate(T, x->p);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}