// Algorithm used
// Step 1: Reverse the infix string. Note that while reversing the string you must interchange left and right parentheses.
// Step 2: Obtain the postfix expression of the infix expression Step 1.
// Step 3: Reverse the postfix expression to get the prefix expression

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// A structure to represent a stack
struct Stack{
    int top;
    int maxSize;
    int *array;
};

// stack and array memory allocation of the size of expression
struct Stack *create(int expression_len){
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->maxSize = expression_len;
    stack->top = -1;
    stack->array = (int *)malloc(stack->maxSize * sizeof(int));
    return stack;
}

// Checking with this function is stack is full or not
int isFull(struct Stack *stack){
    if (stack->top == stack->maxSize - 1)
    {
        printf("Will not be able to push maxSize reached\n");
    }
    // Since array starts from 0, and maxSize starts from 1
    return stack->top == stack->maxSize - 1;
}

// return true if top is -1 i.e stack is empty
int isEmpty(struct Stack *stack){
    return stack->top == -1;
}

// Push function here, inserts value in stack and increments stack top by 1
void push(struct Stack *stack, int item){
    if (isFull(stack)) // checks if stack is full from above function
        return;        // else push
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack *stack){
    if (isEmpty(stack)) // checks if stack is empty from above function
        return INT_MIN; // else pop
    return stack->array[stack->top--];
}

int peek(struct Stack *stack){
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

// A utility function to check if the given character is operand
int checkIfOperand(char check){
    return (check >= 'a' && check <= 'z') || (check >= 'A' && check <= 'Z') || (check >= '0' && check <= '9');
}

// Function to compare precedence; larger the value, higher the precedence
int precedence(char check){
    switch (check){
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;
    }
    return -1;
}

// The driver function for infix to postfix conversion
int getPostfix(char *expression){
    int i, j;

    // Stack size should be equal to expression size for safety
    struct Stack *stack = create(strlen(expression));
    if (!stack){ // just checking is stack was created or not
        return -1;
    }

    for (i = 0, j = -1; expression[i]; ++i){

        if (checkIfOperand(expression[i]))
            expression[++j] = expression[i];

        else if (expression[i] == '(')
            push(stack, expression[i]);

        else if (expression[i] == ')'){
            while (!isEmpty(stack) && peek(stack) != '(')
                expression[++j] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1; // invalid expression
            else
                pop(stack);
        }
        else{ // if an opertor
            while (!isEmpty(stack) && precedence(expression[i]) <= precedence(peek(stack)))
                expression[++j] = pop(stack);
            push(stack, expression[i]);
        }
    }

    // Once all inital expression characters are traversed
    // adding all left elements from stack to exp
    while (!isEmpty(stack))
        expression[++j] = pop(stack);

    expression[++j] = '\0';
}

void reverse(char *exp){
    int size = strlen(exp);
    int j = size, i = 0;
    char temp[size];
    temp[j--] = '\0';
    while (exp[i] != '\0'){
        temp[j] = exp[i];
        j--;
        i++;
    }
    strcpy(exp, temp);
}

void brackets(char *exp){
    int i = 0;
    while (exp[i] != '\0'){
        if (exp[i] == '(')
            exp[i] = ')';
        else if (exp[i] == ')')
            exp[i] = '(';
        i++;
    }
}

void InfixtoPrefix(char *exp){
    //according to the algorithm
    
    // Step 1: Reverse the infix string.
    // reverse string
    reverse(exp);

    // interchange left and right parentheses.
    // change brackets
    brackets(exp);

    // Step 2: Obtain the postfix expression of the infix expression Step 1.
    // get postfix
    getPostfix(exp);

    // Step 3: Reverse the postfix expression to get the prefix expression
    // reverse string again
    reverse(exp);
}

int main(){
    char expression[20];
    printf("\nhie this program converts an infix expression to prefix!, try it out!\n");
    // char expression[] = "((a/b)+c)-(d+(e*f))";
    printf("\nenter an expression to work on:");
    scanf("%s", &expression);
    printf("following is the infix expression: %s \n", expression);
    InfixtoPrefix(expression);
    printf("the conversion to postfix will look like: %s\n", expression);
    printf("\nGood day! keep smiling and ofcourse, take care!\n\n");
}