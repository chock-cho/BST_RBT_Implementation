#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

int main(void) {
    bstree* BST = (bstree*)malloc(sizeof(bstree)); // bstree 구조체 초기화
    BST->root = NULL;

    // sample 노드 데이터 삽입
    int bst_nodeList[] = { 56, 26, 18, 28, 190, 213, 200, 12, 24, 27 };

    for (int i = 0; i < 10; i++) {
        treeInsert(BST, createNode(bst_nodeList[i]));
    }
    // BST 출력
    printf("초기 BST 중위 순회: ");
    inOrderTreeWalk(BST->root);
    printf("\n\n");

    printf("===============================\n");
    printf("BST insert 연산 진행\n");
    printf("===============================\n");

    // 키가 195인 노드 생성 후 삽입 연산 진행
    int k1 = 195;
    treeInsert(BST, createNode(195));

    printf("%d 삽입 후 BST 중위 순회: ", k1);
    inOrderTreeWalk(BST->root);
    printf("\n\n");
    
    printf("===============================\n");
    printf("BST delete 연산 진행\n");
    printf("===============================\n");
    // 키가 26인 노드 찾기
    int k2 = 26;
    bstreeNode* nodeToDelete = treeSearch(BST->root, k2);
    if (nodeToDelete == NULL) {
        printf("키 값이 %d인 노드가 BST에 존재하지 않습니다.\n", k2);
    }
    else {
        bstreeNode* deletedNode = NULL;
        deletedNode = treeDelete(BST, nodeToDelete);
        if (deletedNode == NULL) {
            printf("error caused when deleting the node\n");
        }
        printf("키 값이 %d인 노드가 BST에서 삭제되었습니다.\n", k2);
    }

    // 삭제 후 BST 출력
    printf("Delete연산 후의 BST 중위 순회: ");
    inOrderTreeWalk(BST->root);
    printf("\n");
    return 0;
}
