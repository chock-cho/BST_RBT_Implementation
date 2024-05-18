#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    rbtree* RBT = createRBTree(); // rbtree 구조체 초기화
    
    RBT->nil = (rbtreeNode*)malloc(sizeof(rbtreeNode)); // nil 노드 초기화
    RBT->nil->color = BLACK; // nil 노드는 항상 검정색
    RBT->root = RBT->nil;

    int rbt_nodeList[] = { 7, 3, 18, 10, 22, 8, 11, 26 };

    for (int i = 0; i < 8; i++) {
        RB_Insert(RBT, createRBTreeNode(rbt_nodeList[i], RBT));
    }

    printf("<원래의 RBT>\n ");
    inOrderRBTreeWalk(RBT->root, RBT);

    printf("==========================\n");
    // 키 값이 k1인 노드 삽입
    int k1 = 15;
    rbtreeNode* nodeToInsert = createRBTreeNode(k1, RBT);
    RB_Insert(RBT, nodeToInsert);
    printf("<키 값이 %d인 노드 삽입 후의 RBT> \n", k1);
    inOrderRBTreeWalk(RBT->root, RBT);

    printf("==========================\n");
    // 키 값이 k2인 노드 삭제
    int k2 = 7;
    rbtreeNode* nodeToDelete = rbtreeSearch(RBT->root, RBT, k2);

    if (nodeToDelete != RBT->nil) {
        RB_Delete(RBT, nodeToDelete);
    }
    // 키 값이 15인 삭제 후 중위 순회 출력
    printf("<키 값이 %d인 노드 삭제 후의 RBT> \n",k2);
    inOrderRBTreeWalk(RBT->root, RBT);
    printf("\n");
    return 0;
}
