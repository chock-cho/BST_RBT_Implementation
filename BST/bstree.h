#pragma once
#ifndef BSTREE_H
#define BSTREE_H

/* BST node 구조체 정의 */
typedef struct bstreeNode {
    int key;
    struct  bstreeNode* left, * right, * p;
} bstreeNode;

typedef struct {
    bstreeNode* root;
}bstree;

bstreeNode* createNode(int k);
void inOrderTreeWalk(bstreeNode* root); // 중위순회
void preOrderTreeWalk(bstreeNode* root); // 전위순회
void postOrderTreeWalk(bstreeNode* root); // 후위순회
bstreeNode* treeSearch(bstreeNode* root, int k); // key값이 k인 노드 찾아서 반환하는 함수(재귀적)
bstreeNode* iterative_treeSearch(bstreeNode* root, int key); // key값이 k인 노드 찾아서 반환하는 함수(순환적)
bstreeNode* treeMin(bstreeNode* root); //BST에서 key값이 최소인 노드 찾기
bstreeNode* treeMax(bstreeNode* root); //BST에서 key값이 최대인 노드 찾기
bstreeNode* treeSuccessor(bstreeNode* x); //노드 x의 직후 원소 찾기
bstreeNode* treeDelete(bstree* T, bstreeNode* z); // key값이 z인 노드 BST에서 삭제하는 연산
void treeInsert(bstree* T, bstreeNode* z); // key값이 z인 노드 BST에 삽입하는 연산

#endif