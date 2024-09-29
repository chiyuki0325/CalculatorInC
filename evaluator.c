#include <stdio.h>
#include "evaluator.h"

int evaluate(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->type == NUMBER) {
        return root->token.number;
    }
    int left = evaluate(root->left);
    int right = evaluate(root->right);
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
            return left % right;
        default:
            return 0;
    }
}