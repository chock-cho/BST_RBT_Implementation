#pragma once
#ifndef RBTREE_H
#define RBTREE_H

typedef enum NodeColor { RED, BLACK }Color;

typedef struct rbtreeNode {
    int key;
    Color color;
    struct rbtreeNode* left, * right, * p;          // ����, ������, �θ� ��� ����
} rbtreeNode;

typedef struct {
    rbtreeNode* root;
    rbtreeNode* nil;
} rbtree;

/*      RBT ����     */
rbtree* createRBTree(void);   // ���ο� ���� �� Ʈ�� ���� 
rbtreeNode* createRBTreeNode(int k, rbtree *T); // ���ο� ��� ����
void leftRotate(rbtree* T, rbtreeNode* x);               // ���� ȸ��
void rightRotate(rbtree* T, rbtreeNode* x);              // ������ ȸ��
void RB_Insert(rbtree* T, rbtreeNode *x);                // ���� ����
void RB_Insert_FixUp(rbtree* T, rbtreeNode* x);          // fixedUp ����(���� ���߱� ����)
void RB_Delete(rbtree* T, rbtreeNode *x); // ����� Ʈ���� �޸� ��ȯ 
void RB_Delete_FixUp(rbtree* T, rbtreeNode* x);          // fixedUp ����(���� ���߱� ����)

/*      BST�� �⺻���� ����      */
void freeRBNode(rbtree* T, rbtreeNode* x);
void freeRBTree(rbtree* T);
void inOrderRBTreeWalk(rbtreeNode* root, rbtree* T); // ������ȸ
//void preOrderRBTreeWalk(rbtreeNode* root, rbtree* T); // ������ȸ
//void postOrderRBTreeWalk(rbtreeNode* root, rbtree* T); // ������ȸ
rbtreeNode* rbtreeSearch(rbtreeNode* x, rbtree* RBT, int k); // key���� k�� ��� ã�Ƽ� ��ȯ�ϴ� �Լ�(�����)
//rbtreeNode* iterative_rbtreeSearch(rbtreeNode* root, int k); // key���� k�� ��� ã�Ƽ� ��ȯ�ϴ� �Լ�(��ȯ��)
rbtreeNode* rbtreeMin(rbtree* T, rbtreeNode* root); //BST���� key���� �ּ��� ��� ã��
//rbtreeNode* rbtreeMax(rbtreeNode* root); //BST���� key���� �ִ��� ��� ã��
//rbtreeNode* rbtreeSuccessor(rbtreeNode* x); //��� x�� ���� ���� ã��
#endif

/*      �߰������� �ʿ��� RBT ����         */
const char* getColor(Color color);  // ����� ���� ���