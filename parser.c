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

ListNode* current;

void printCurrent() {
    switch (current->type) {
        case NUMBER:
            printf("NUMBER: %d\n", current->token.number);
            break;
        case OPERATOR:
            printf("OPERATOR: %c\n", current->token.op);
            break;
        case LEFT_BRACKET:
            printf("LEFT_BRACKET\n");
            break;
        case RIGHT_BRACKET:
            printf("RIGHT_BRACKET\n");
            break;
        default:
            break;
    }
}

/* 由于先乘除后加减，所以先解析乘除表达式，三个函数优先级递减 */

TreeNode* parseFactor() {
    current = current->next;
    /* 解析因子，如果为数字则前进，否则进入括号 */
    if (current->type == NUMBER) {
        /* 数字 */
        return newTreeNode(current->token, NUMBER);
    } else if (current->type == LEFT_BRACKET) {
        /* 左括号，进入括号 */
        TreeNode* node = parseExpression();  /* 递归解析 */
        current = current->next;
        if (current->type != RIGHT_BRACKET) {
            /* 没有右括号，报错退出 */
            printf("SyntaxError: Expecting a right bracket\n");
            return NULL;
        }
        return node;
    } else {
        printf("SyntaxError: Expecting a number or a left bracket\n");
        return NULL;
    }
}

TreeNode* parseTerm() {
    /* 解析乘法和除法表达式 */
    TreeNode* node = parseFactor();
    current = current->next;
    while (current->type == OPERATOR && (current->token.op == '*' || current->token.op == '/')) {
        TreeNode* operatorNode = newTreeNode(current->token, OPERATOR);
        operatorNode->left = node;
        operatorNode->right = parseFactor();
        node = operatorNode;
        current = current->next;
    }
    current = current->prev;
    return node;
}
    
TreeNode* parseExpression() {
    /* 解析加法和减法表达式，类似 parseTerm，不过上升了一个优先级 */
    TreeNode* node = parseTerm();
    current = current->next;
    while (current->type == OPERATOR && (current->token.op == '+' || current->token.op == '-')) {
        TreeNode* operatorNode = newTreeNode(current->token, OPERATOR);
        operatorNode->left = node;
        operatorNode->right = parseTerm();
        current = current->next;
        node = operatorNode;    
    }
    current = current->prev;
    return node;
}

TreeNode* runParser(ListNode* head) {
    current = head;
    return parseExpression();
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