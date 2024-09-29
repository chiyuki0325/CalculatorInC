#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int value;
} Number;

typedef enum {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
} OperatorType; 

typedef struct {
    OperatorType type;
} Operator;

typedef union {
    Number number;
    Operator op;
} Token;

typedef enum {
    LEFT_BRACKET,
    RIGHT_BRACKET,
    NUMBER,
    OPERATOR,
    NONE
} TokenType;

/* 单向链表 */
typedef struct ListNode {
    Token token;
    TokenType type;
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