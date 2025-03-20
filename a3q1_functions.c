#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"


Variable variables[10];
int varCount = 0;


// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node* createNode(char *data){
	Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node* parseExpression(char *expr) {
    if (*expr == '(') {
        int count = 0;
        int i = 0;
        char leftExpr[100];
        char rightExpr[100];
        char operator;

        // Find the main operator
        for (i = 1; expr[i] != '\0'; i++) {
            if (expr[i] == '(') count++;
            if (expr[i] == ')') count--;
            if (count == 0 && (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/')) {
                operator = expr[i];
                break;
            }
        }

        // Extract left sub-expression
        strncpy(leftExpr, expr + 1, i - 1);
        leftExpr[i - 1] = '\0';

        // Extract right sub-expression
        strcpy(rightExpr, expr + i + 1);
        rightExpr[strlen(rightExpr) - 1] = '\0'; // Remove trailing parenthesis

        // Create operator node
        Node *node = createNode((char[]){operator, '\0'});
        node->left = parseExpression(leftExpr);
        node->right = parseExpression(rightExpr);
        return node;
    } else {
        // If not parenthesized, it's a single operand
        return createNode(expr);
    }
}


// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root){
    if (root == NULL)
        return;
    printf("%s ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root){
    if (root == NULL)
        return;
    // If the node is an operator, add parentheses
    if (root->left || root->right)
        printf("(");
    inorder(root->left);
    printf("%s", root->data);
    inorder(root->right);
    if (root->left || root->right)
        printf(")");
}

// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root){
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%s ", root->data);
}

// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root){
    if (root == NULL)
        return;
    // Check if node contains a variable
    if (isalpha(root->data[0])) {
        int found = 0;
        for (int i = 0; i < varCount; i++) {
            if (strcmp(variables[i].varName, root->data) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Enter value for %s: ", root->data);
            scanf("%f", &variables[varCount].value);
            strcpy(variables[varCount].varName, root->data);
            varCount++;
        }
    }

    promptVariables(root->left);
    promptVariables(root->right);
}

// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root){
	if (root == NULL)
        return 0;

    if (isdigit(root->data[0]) || root->data[0] == '.') {
        return atof(root->data);
    }

    if (isalpha(root->data[0])) {
        for (int i = 0; i < varCount; i++) {
            if (strcmp(variables[i].varName, root->data) == 0) {
                return variables[i].value;
            }
        }
        return 0;
    }

    float left_Value = calculate(root->left);
    float right_Value = calculate(root->right);

    switch (root->data[0]) {
        case '+': return left_Value + right_Value;
        case '-': return left_Value - right_Value;
        case '*': return left_Value * right_Value;
        case '/':
            if (right_Value == 0) {
                return -1;
            }
            return left_Value / right_Value;
        default:
            //printf("Error, Unknown operator %s\n", root->data);
            return -2;
}
}


