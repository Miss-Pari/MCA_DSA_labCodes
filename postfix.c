//structure based stack--implementation of Stack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//A structure to represent a stack
//storing string in integer array, this will not give error as values will be stored in ASCII and returned in ASCII thus, returned as string again
struct Stack {
    int top;
    int maxSize;
    int *array;
};

//stack and array memory allocation of the size of expression 
struct Stack *create(int expression_len){
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->maxSize = expression_len;
    stack->top = -1;
    stack->array = (int *)malloc(stack->maxSize * sizeof(int));
    return stack;
}

//Checking with this function is stack is full or not
int isFull(struct Stack *stack)
{
    if (stack->top == stack->maxSize - 1)
    {
        printf("Will not be able to push maxSize reached\n");
    }
    // Since array starts from 0, and maxSize starts from 1
    return stack->top == stack->maxSize - 1;
}

//return true if top is -1 i.e stack is empty
int isEmpty(struct Stack *stack){
    return stack->top == -1;
}

// Push function here, inserts value in stack and increments stack top by 1
void push(struct Stack *stack, int item){
    if (isFull(stack))  //checks if stack is full from above function
        return;             //else push
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack *stack){
    if (isEmpty(stack))  //checks if stack is empty from above function
        return INT_MIN;    //else pop
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
int precedence(char check)
{
    switch (check)
    {
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
int covertInfixToPostfix(char *exp){   
    // printf("\ncontrol flag\n");
    int i, j;
    // create stack that is equal to expression's size
    struct Stack *stack = create (strlen (exp));
    if (!stack){ // check if stack was created or not
        printf("\nError🧠! stack not created sweetie!");
        return -1;
    }
    // printf("\nstack created\n");

    for (i = 0, j = -1; exp[i]; ++i){
        //check if character is operand or not
        // and this adding to the output.
        if (checkIfOperand(exp[i]))
            exp[++j] = exp[i];

        else if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
            push(stack, exp[i]);

        else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']'){
            if (exp[i] == ')'){
                while (!isEmpty(stack) && peek(stack) != '(')
                    exp[++j] = pop(stack);
                pop(stack);  // pops '('
            }

            if (exp[i] == ']'){
                while (!isEmpty(stack) && peek(stack) != '[')
                    exp[++j] = pop(stack);
                pop(stack); // pops '['
            }

            if (exp[i] == '}'){
                while (!isEmpty(stack) && peek(stack) != '{')
                    exp[++j] = pop(stack);
                pop(stack);  // pops '}'
            }
        }
        else{ // if an operator
            while (!isEmpty(stack) && precedence(exp[i]) <= precedence(peek(stack)))
                exp[++j] = pop(stack);
            push(stack, exp[i]);
        }
    }

//Once all initial expression characters are traversed adding all left elements from stack
while (!isEmpty(stack))
    exp[++j] = pop(stack);

exp[++j] = '\0';
printf("%s", exp);
}

void main(){
    char expression[20];
    printf("\nhie this program converts an infix expression to postfix!, try it out!\n");
    // char expression[] = "{[p(2*7)]-d}";
    // char expression[] = "(a-b)*(c+d)";
    printf("\nenter an expression to work on:");
    scanf("%s", &expression);
    printf("following is the infix expression: %s \n", expression);
    printf("the conversion to postfix will look like: ");
    covertInfixToPostfix (expression);
    printf("\nGood day! keep smiling and ofcourse, take care!\n\n");
}