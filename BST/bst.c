// BST 연산 구현
#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>

// 새 노드 생성
bstreeNode* createNode(int k) {
    bstreeNode* newNode = (bstreeNode*)calloc(1, sizeof(bstreeNode));             // 삽입할 노드 z 생성
    newNode->key = k;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->p = NULL; // 새 노드의 부모를 초기화
    return newNode;
}

// 전위 순회 : V L R
void preOrderTreeWalk(bstreeNode* x) {
    if (x != NULL) {
        printf("%d ", x->key);
        preOrderTreeWalk(x->left);
        preOrderTreeWalk(x->right);
    }
}

// 중위 순회: L V R
void inOrderTreeWalk(bstreeNode* x) {
    if (x != NULL) {
        inOrderTreeWalk(x->left);
        printf("%d ", x->key);
        inOrderTreeWalk(x->right);
    }
}

// 후위 순회: L R V
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

// x의 직후 노드 찾기 연산
bstreeNode* treeSuccessor(bstreeNode* x) {
    if (x->right != NULL)
        return treeMin(x->right);           // 직후 노드를 오른쪽 서브트리의 가장 작은 노드로 정의
    bstreeNode* y = x->p;
    while (y != NULL && x == y->right) {        // x의 부모 노드가 NULL이 아니고(아직 루트에 도달하지 않았고), x가 오른쪽 자식 노드였다면
        x = y;                                  // 한칸 씩 위로 올라간다.
        y = y->p;
    }
    return y;
}

// 이진 탐색 트리에 노드 삽입
void treeInsert(bstree* T, bstreeNode* z) {
    bstreeNode* y = NULL;      // 초기화(root 노드의 부모 노드 = null)
    bstreeNode* x = T->root;   // x는 현재의 root 노드부터 시작

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y; // 새 노드의 부모를 설정

    if (y == NULL)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

bstreeNode* treeDelete(bstree* T, bstreeNode* z) {
    bstreeNode* y = NULL;                           // y는 삭제할 노드
    /* Determine which node to splice out: either z or z's successor */
    if (z->left == NULL || z->right == NULL)        // 삭제할 노드의 양쪽에 자식 노드가 없거나, 하나만 있는 경우
        y = z;                                      // case 0 or 1(case 0: 자식 노드가 아예 없음, case 1: 자식 노드가 하나만 있음)   
    else
        y = treeSuccessor(z);                      //  case 2: 양쪽 자식 노드 모두 존재한다면
                                                   // y는 삭제할 노드의 직후 노드

    bstreeNode* x = NULL;     

    /* set x to non-NIL child of x, or to NIL if y has no children */
    // case 1) 한쪽 노드만 있는 경우
    if (y->left != NULL)                            // y의 왼쪽 자식 노드가 있다면
        x = y->left;                                // x는 y의 왼쪽 자식 노드
    else                                            // y의 오른쪽 자식 노드가 있다면
        x = y->right;                               // x는 y의 오른쪽 자식 노드

    /* y is removed from tree by manipulating pointers of p[y] and x */
    if (x != NULL)                                 // case 1, 2
        x->p = y->p;                                // y는 삭제할 노드에 딸려있는 포인터 값


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