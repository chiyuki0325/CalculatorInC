#ifndef TYPES_H
#define TYPES_H

typedef union {
    double number;
    char op;
} Token;

typedef enum {
    LEFT_BRACKET,
    RIGHT_BRACKET,
    NUMBER,
    OPERATOR,
    NONE
} TokenType;

/*
 * 一开始写的是单向，但是写到 parser 时有后退的需求，所以改成了双向链表
 */
typedef struct ListNode {
    Token token;
    TokenType type;
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

typedef enum {
    IDLE,
    NUMBERS,
    OPERATORS,
    BRACKETS
} LexerState;

/* 二叉树 */
typedef struct TreeNode {
    Token token;
    TokenType type;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
#endif