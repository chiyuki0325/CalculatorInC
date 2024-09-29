#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

TreeNode* newTreeNode(
    Token token,
    TokenType type
) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->token = token;
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* parseExpression(ListNode* head) {

}

void traversalPrint(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    if (root->type == OPERATOR) printf("(");
    traversalPrint(root->left);
    switch (root->type) {
        case NUMBER:
            printf("%d", root->token.number);
            break;
        case OPERATOR:
            printf("%c", root->token.op);
            break;
        default:
            break;
    }
    traversalPrint(root->right);
    if (root->type == OPERATOR) printf(")");
}