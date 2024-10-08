#include "types.h"
#include "utils.h"

TreeNode* newTreeNode(Token token, TokenType type);
TreeNode* parseExpression();
TreeNode* parseTerm();
TreeNode* parseFactor();
TreeNode* runParser(ListNode* head);
void traversalPrint(TreeNode* root);