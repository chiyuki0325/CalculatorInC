#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

int main() {
    char expression[512]; /* 初始化缓冲区 */

    printf("Please input an integer expression: ");
    fgets(expression, 512, stdin); /* 从标准输入读取表达式 */

    /* 为了方便后续处理，给表达式末尾添加一个空格 */
    expression[strlen(expression) - 1] = ' ';
    expression[strlen(expression)] = '\0';

    /* 第一步：词法分析 */
    ListNode* head = runLexer(expression);

    /* 错误处理 */
    if (head == NULL) {
        return 1;
    }

    /* 第二步：语法分析 */
    TreeNode* root = runParser(head);

    /* 错误处理 */
    if (root == NULL) {
        return 1;
    }

    /* 第三步：计算表达式 */
    traversalPrint(root);
    printf(" = %d\n", evaluate(root));
    
    return 0;
}