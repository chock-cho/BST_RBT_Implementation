#pragma once
#ifndef BSTREE_H
#define BSTREE_H

/* BST node ����ü ���� */
typedef struct bstreeNode {
    int key;
    struct  bstreeNode* left, * right, * p;
} bstreeNode;

typedef struct {
    bstreeNode* root;
}bstree;

bstreeNode* createNode(int k);
void inOrderTreeWalk(bstreeNode* root); // ������ȸ
void preOrderTreeWalk(bstreeNode* root); // ������ȸ
void postOrderTreeWalk(bstreeNode* root); // ������ȸ
bstreeNode* treeSearch(bstreeNode* root, int k); // key���� k�� ��� ã�Ƽ� ��ȯ�ϴ� �Լ�(�����)
bstreeNode* iterative_treeSearch(bstreeNode* root, int key); // key���� k�� ��� ã�Ƽ� ��ȯ�ϴ� �Լ�(��ȯ��)
bstreeNode* treeMin(bstreeNode* root); //BST���� key���� �ּ��� ��� ã��
bstreeNode* treeMax(bstreeNode* root); //BST���� key���� �ִ��� ��� ã��
bstreeNode* treeSuccessor(bstreeNode* x); //��� x�� ���� ���� ã��
bstreeNode* treeDelete(bstree* T, bstreeNode* z); // key���� z�� ��� BST���� �����ϴ� ����
void treeInsert(bstree* T, bstreeNode* z); // key���� z�� ��� BST�� �����ϴ� ����

#endif