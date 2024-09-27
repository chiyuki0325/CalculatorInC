#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

int main() {
    char expression[512]; /* 初始化缓冲区 */

    printf("Please input an expression (only integer calculation is supported): ");
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

    printNodes(head);
    return 0;
}