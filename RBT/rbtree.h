#pragma once
#ifndef RBTREE_H
#define RBTREE_H

typedef enum NodeColor { RED, BLACK }Color;

typedef struct rbtreeNode {
    int key;
    Color color;
    struct rbtreeNode* left, * right, * p;          // 왼쪽, 오른쪽, 부모 노드 정의
} rbtreeNode;

typedef struct {
    rbtreeNode* root;
    rbtreeNode* nil;
} rbtree;

/*      RBT 연산     */
rbtree* createRBTree(void);   // 새로운 레드 블랙 트리 생성 
rbtreeNode* createRBTreeNode(int k, rbtree *T); // 새로운 노드 생성
void leftRotate(rbtree* T, rbtreeNode* x);               // 왼쪽 회전
void rightRotate(rbtree* T, rbtreeNode* x);              // 오른쪽 회전
void RB_Insert(rbtree* T, rbtreeNode *x);                // 삽입 연산
void RB_Insert_FixUp(rbtree* T, rbtreeNode* x);          // fixedUp 연산(균형 맞추기 위한)
void RB_Delete(rbtree* T, rbtreeNode *x); // 레드블랙 트리의 메모리 반환 
void RB_Delete_FixUp(rbtree* T, rbtreeNode* x);          // fixedUp 연산(균형 맞추기 위한)

/*      BST의 기본적인 연산      */
void freeRBNode(rbtree* T, rbtreeNode* x);
void freeRBTree(rbtree* T);
void inOrderRBTreeWalk(rbtreeNode* root, rbtree* T); // 중위순회
//void preOrderRBTreeWalk(rbtreeNode* root, rbtree* T); // 전위순회
//void postOrderRBTreeWalk(rbtreeNode* root, rbtree* T); // 후위순회
rbtreeNode* rbtreeSearch(rbtreeNode* x, rbtree* RBT, int k); // key값이 k인 노드 찾아서 반환하는 함수(재귀적)
//rbtreeNode* iterative_rbtreeSearch(rbtreeNode* root, int k); // key값이 k인 노드 찾아서 반환하는 함수(순환적)
rbtreeNode* rbtreeMin(rbtree* T, rbtreeNode* root); //BST에서 key값이 최소인 노드 찾기
//rbtreeNode* rbtreeMax(rbtreeNode* root); //BST에서 key값이 최대인 노드 찾기
//rbtreeNode* rbtreeSuccessor(rbtreeNode* x); //노드 x의 직후 원소 찾기
#endif

/*      추가적으로 필요한 RBT 연산         */
const char* getColor(Color color);  // 노드의 색깔 출력