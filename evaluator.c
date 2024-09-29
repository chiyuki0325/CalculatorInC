#include <stdio.h>
#include "evaluator.h"

double evaluate(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->type == NUMBER) {
        return root->token.number;
    }
    double left = evaluate(root->left);
    double right = evaluate(root->right);
    switch (root->token.op) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        case '%':
            /* 检查是否为整数 */
            if (left == (int)left && right == (int)right) {
                return (int)left % (int)right;
            } else {
                printf("TypeError: Modulo operation is only supported for integers\n");
                return 0;
            }
        default:
            return 0;
    }
}