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


// 출력 함수
#include <stdio.h>
#include "rbtree.h"

void inOrderRBTreeWalk(rbtreeNode* x, rbtree* T) {
    if (x == T->nil) return;
    inOrderRBTreeWalk(x->left, T);

    // 부모 노드 키 값 설정
    char parentKey[20];
    if (x->p == T->nil) {
        snprintf(parentKey, sizeof(parentKey), "nil");
    }
    else {
        snprintf(parentKey, sizeof(parentKey), "%d", x->p->key);
    }

    // 왼쪽 자식 노드 키 값 설정
    char leftKey[20];
    if (x->left == T->nil) {
        snprintf(leftKey, sizeof(leftKey), "nil");
    }
    else {
        snprintf(leftKey, sizeof(leftKey), "%d", x->left->key);
    }

    // 오른쪽 자식 노드 키 값 설정
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


// 메모리 해제 함수
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
/*      왼쪽 회전 연산     */
void leftRotate(rbtree* T, rbtreeNode* x) {
    rbtreeNode* y = x->right;                                  // y 설정: y는 x의 오른쪽 자식 노드
    x->right = y->left;                                         // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로 만든다.

    if (y->left != T->nil)                                         // y의 왼쪽 자식 노드가 nil 노드가 아닌 내부노드라면
        y->left->p = x;                                         // 부모로 x를 연결한다.

    y->p = x->p;                                                    // x의 부모를 y로 연결한다.

    if (x->p == T->nil)                                            // CASE 1. 연결한 x의 부모가 nil 노드라면(레드블랙 트리 상에서의 루트)
        T->root = y;                                                      // x가 루트인 경우, y가 새로운 루트가 된다.
    else if (x == x->p->left)                                    // CASE 2. x가 부모의 왼쪽 자식인 경우
        x->p->left = y;
    else                                                        // CASE 3. x가 부모의 오른쪽 자식인 경우
        x->p->right = y;

    y->left = x;                                             // x를 y의 왼쪽 자식으로 만든다.
    x->p = y;                                               // x의 부모를 y로 설정한다.
}

/*      오른쪽 회전 연산     */
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

/*      레드 블랙 트리 삽입 연산    */
void RB_Insert(rbtree* T, rbtreeNode *z) {
    rbtreeNode* y = T->nil;
    rbtreeNode* x = T->root;                                        //x를 T의 루트 노드를 가리키는 포인터값으로 설정한다.

    /* 루트에서부터 쭉 내려오면서, BST 삽입 연산처럼 수행한다. */
    while (x != T->nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y; //z의 부모를 설정한다.
    if (y == T->nil) //CASE 1) z의 부모가 sentinel 노드라면(즉, z가 삽입될 자리가 루트)
        T->root = z;
    else if (z->key < y->key)
        y->left = z; // CASE 2) z가 부모의 왼쪽 자식인 경우 
    else
        y->right = z; // CASE 3) z가 부모의 오른쪽 자식인 경우

    z->left = T->nil;
    z->right = T->nil;
    z->color = RED; // 삽입되는 노드의 색깔은 항상 red로 설정
    RB_Insert_FixUp(T, z);
}

/*      레드-블랙 트리 삽입 후 보정 연산        */
void RB_Insert_FixUp(rbtree* T, rbtreeNode* z) {
    rbtreeNode* y;

    while (z->p != T->nil && z->p->color == RED) {
        if (z->p == z->p->p->left) {         // 부모 노드가 조부모 노드의 왼쪽 자식이라면
            y = z->p->p->right;              // 삼촌 노드는 조부모 노드의 오른쪽 자식 노드
            /* CASE 1: 삼촌 노드 색이 레드인 경우 */
            if (y->color == RED) {
                z->p->color = BLACK; // 부모 노드의 색깔을 블랙으로 만든다.
                y->color = BLACK;    // 삼촌 노드의 색깔도 블랙으로 만든다.
                z->p->p->color = RED; // 조부모 노드의 색은 레드로 만든다.
                z = z->p->p;          // 두 칸 위로 거슬러 올라가 진행한다.(Bottom-up)
            }
            /* 삼촌 노드 색이 블랙인 경우 */
            else {
                if (z == z->p->right) {// CASE 2. 삼촌 노드 색이 블랙이고, z가 오른쪽 자식인 경우
                    z = z->p;         // 부모 노드에 대해
                    leftRotate(T, z); // 왼쪽 회전 연산 수행
                }
                // CASE 3. 삼촌 노드 색이 블랙이고, z가 오른쪽 자식인 경우
                z->p->color = BLACK; // 부모노드의 색깔을 블랙으로 만들어준다.
                z->p->p->color = RED; // 조부모 노드 색깔을 레드로 만들어준다.
                rightRotate(T, z->p->p); // 오른쪽으로 회전
            }
        }
        else {                                  // 부모 노드가 조부모 노드의 오른쪽 자식이라면
            y = z->p->p->left;                  // 삼촌 노드는 조부모 노드의 왼쪽 자식
            /* CASE 1: 삼촌 노드 색이 레드인 경우 */
            if (y->color == RED) {
                z->p->color = BLACK;     // 부모 노드의 색깔을 블랙으로 변경
                y->color = BLACK;        // 삼촌 노드의 색깔을 블랙으로 변경
                z->p->p->color = RED;    // 조부모 노드의 색깔을 레드로 변경
                z = z->p->p;             // 두 칸 위로 거슬러 올라가 진행한다.
            }
            /* 삼촌 노드 색이 블랙인 경우 */
            else {
                if (z == z->p->left) { // CASE 2. 삼촌 노드의 색이 블랙이고, z가 왼쪽 자식인 경우
                    z = z->p;         // 부모 노드에 대해
                    rightRotate(T, z); // 오른쪽 회전 연산 수행
                }
                // CASE 3. 삼촌 노드 색이 블랙이고, z가 오른쪽 자식인 경우
                z->p->color = BLACK; // 부모노드의 색깔을 블랙으로 만들어준다.
                z->p->p->color = RED; // 조부모 노드 색깔을 레드로 만들어준다.
                leftRotate(T, z->p->p); // 오른쪽으로 회전
            }
        }
    }
    T->root->color = BLACK; // 루트 노드의 색깔은 항상 블랙
}

void RB_Transplant(rbtree* T, rbtreeNode* u, rbtreeNode* v) {
    if (u->p == T->nil) {      // 삭제될 노드가 root 인 경우
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

/*      RBT 삭제 후 보정 연산    */

void RB_Delete_FixUp(rbtree* T, rbtreeNode* x) {
    while (x != T->nil && x != T->root && x->color == BLACK) {
        if (x == x->p->left) {               // 삭제될 x가 왼쪽 자식인 경우
            rbtreeNode* w = x->p->right;   // w는 x의 형제 노드라고 가정하자
            /* CASE 1: x의 형제 w가 레드인 경우 */
            if (w->color == RED) {
                w->color = BLACK;           // 형제 노드의 색깔을 블랙으로 바꾼다.
                x->p->color = RED;          // 부모 노드의 색깔을 레드로 바꾼다.
                leftRotate(T, x->p);        // 부모 노드에 대해 왼쪽 회전 연산 수행
                w = x->p->right;            // 새로운 형제를 설정한다.
            }

            /* CASE 2: x의 형재 w가 블랙이고, w의 두 자식 노드도 모두 블랙인 경우 */
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;             // 형제 노드의 색깔을 레드로 바꾼다.
                x = x->p;                   // x를 x의 부모 노드로 설정한다.
            }
            else {
                /* CASE 3: x의 형제 w가 블랙이고, w의 왼쪽 자식 노드는 레드, 오른쪽 자식 노드는 블랙인 경우 */
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;     // w의 왼쪽 자식 노드 색깔을 블랙으로 바꾼다.
                    w->color = RED;             // w의 색깔을 레드로 바꾼다.
                    rightRotate(T, w);          // w에 대해 오른쪽 회전 연산 수행
                    w = x->p->right;            // 이제 형제 노드는 x의 부모 노드의 오른쪽 자식 노드 
                }

                /* CASE 4: x의 형제 w가 BLACK이고 w의 오른쪽 자식이 RED인 경우 */
                w->color = x->p->color;        // 형제 노드를 부모의 색으로 바꾼다.
                x->p->color = BLACK;           // 부모 노드를 BLACK으로 바꾼다.
                w->right->color = BLACK;        // 형제의 오른쪽 자식을 BLACK으로 바꾼다.
                leftRotate(T, x->p);           // 부모 노드에 대해 좌회전 수행
                x = T->root;
            }
        }
        else {                              // 삭제될 x가 오른쪽 자식인 경우
            rbtreeNode* w = x->p->left;    // 형제 노드 w는 왼쪽 자식 노드

            /* CASE 1: x의 형제 w가 레드인 경우 */
            if (w->color == RED) {
                w->color = BLACK;           // 형제 노드의 색깔을 블랙으로 만들어준다.
                x->p->color = RED;          // 부모 노드의 색깔을 레드로 만든다.
                rightRotate(T, x->p);       // 부모 노드에 대해 오른쪽 회전 연산 수행
                w = x->p->left;             // 설정된 새로운 형제는 부모 노드의 왼쪽 자식 노드
            }

            /* CASE 2: x의 형제 w가 블랙이고, w의 두 자식 노드도 모두 블랙인 경우 */
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->p;
            }
            else {
                /* CASE 3: x의 형제 w가 블랙이고, w의 오른쪽 자식 노드는 레드, 왼쪽 자식 노드는 블랙인 경우 */
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(T, w);
                    w = x->p->left;
                }

                /* CASE 4: x의 형제 w가 블랙이고, w의 왼쪽 자식이 레드인 경우 */
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