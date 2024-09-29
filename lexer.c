#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

ListNode* newTokenNode(
    Token token,
    TokenType type
) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->token = token;
    node->type = type;
    node->next = NULL;
    return node;
}

int numberCache = 0;

ListNode* runLexer(
    char *expression
) {
    LexerState state = IDLE;
    ListNode* head = newTokenNode((Token){}, NONE); /* 表头为空 */
    ListNode* currentNode = head;
    int position = 0;
    int expressionLength = strlen(expression);

    while (position < expressionLength) {
        char currentChar = expression[position];
        switch (state) {
            case IDLE:
                if (currentChar == '(') {
                    /* 左括号 */
                    currentNode->next = newTokenNode((Token){}, LEFT_BRACKET);
                    currentNode = currentNode->next;
                    state = BRACKETS;
                } else if (currentChar == ')') {
                    /* 右括号 */
                    currentNode->next = newTokenNode((Token){}, RIGHT_BRACKET);
                    currentNode = currentNode->next;
                    state = BRACKETS;
                } else if (isdigit(currentChar)) {
                    /* 数字 */
                    numberCache = currentChar - '0'; /* 数字字符的 ASCII 码减去 0 的 ASCII 码，得到数字本身 */
                    state = NUMBERS;
                } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
                    /* 运算符 */
                    currentNode->next = newTokenNode((Token){.op = currentChar}, OPERATOR);
                    currentNode = currentNode->next;
                    state = OPERATORS;
                } else if (currentChar == ' ') {
                    /* 空格 */
                } else {
                    printf("SyntaxError: Unexpected character at position %d\n", position);
                    return NULL;
                }
                break;
            case NUMBERS:
                if (isdigit(currentChar)) {
                    /* 下一位还是数字 */
                    numberCache = numberCache * 10 + (currentChar - '0');
                } else {
                    currentNode->next = newTokenNode((Token){.number = numberCache}, NUMBER);
                    currentNode = currentNode->next;
                    state = IDLE;
                    position--;
                }
                break;
            case OPERATORS:
                if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
                    /* 之前已经添加过一个操作符，并且将其添加到了链表中 */
                    /* 再次遇到操作符，就需要报错 */
                    printf("SyntaxError: Unexpected operator at position %d\n", position);
                    return NULL;
                } else {
                    state = IDLE;
                    position--;
                }
                break;
            case BRACKETS:
                if (currentChar == '(' || currentChar == ')') {
                    /* 再次遇到括号，就需要报错 */
                    printf("SyntaxError: Unexpected bracket at position %d\n", position);
                    return NULL;
                } else {
                    state = IDLE;
                    position--;
                }
        }
        position++;
    }

    return head;
}

void printNodes(
    ListNode* head
) {
    ListNode* currentNode = head->next;
    while (currentNode != NULL) {
        if (currentNode->type == NUMBER) {
            printf("NUM: %d\n", currentNode->token.number);
        } else if (currentNode->type == OPERATOR) {
            printf("OPR: %c\n", currentNode->token.op);
        } else if (currentNode->type == LEFT_BRACKET) {
            printf("LBR: (\n");
        } else if (currentNode->type == RIGHT_BRACKET) {
            printf("RBR: )\n");
        }
        currentNode = currentNode->next;
    }
}