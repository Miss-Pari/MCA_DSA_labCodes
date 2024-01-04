#include <stdio.h>
#include <stdlib.h>
#define bool int


struct Oprands{     //structure of stack nodes
    char oprand;
    struct Oprands* next;
};

void push(struct Oprands** top, int new);
int pop(struct Oprands** top);

bool match(char LHS, char RHS){         //function to compare
    if (LHS == '(' && RHS == ')')
        return 1;
    else if (LHS == '{' && RHS == '}')
        return 1;
    else if (LHS == '[' && RHS == ']')
        return 1;
    else
        return 0;
}

bool balanced(char check[]){
    struct Oprands* stack = NULL;
    int cnt = 0;
    while (check[cnt]){         //for every bracket
        //only if opening bracket
        if (check[cnt]=='{' ||check[cnt]=='(' ||check[cnt]=='[')
            push(&stack, check[cnt]);
        //only if closing bracket
        if (check[cnt]=='}' ||check[cnt]==')'||check[cnt]==']') {
            if(stack==NULL){
                printf("no previous data to compare with hence, \n");
                return 0; //false -> not balanced
            }else if (!match(pop(&stack), check[cnt]))
                return 0;
        }
        cnt = cnt + 1;   
    }

    if (stack == NULL)
        return 1; // balanced
    else
        return 0; // not balanced
}

void push(struct Oprands** top, int new){
    struct Oprands* new_node = (struct Oprands*)malloc(sizeof(struct Oprands));
    new_node->oprand=new;
    new_node->next=(*top);
    (*top)=new_node;
}

int pop(struct Oprands** top){
    char previous;
    struct Oprands* new_top;
    // If stack is empty then error
    if (*top == NULL) {
        printf("Stack overflow n");
        getchar();
        exit(0);
    }else{
        new_top = *top;
        previous = new_top->oprand;
        *top = new_top->next;
        return previous;
    }
}

int main(){
    char check[50] ;
    // char check[50] = "]";

    printf("Enter string of parenthesis to check for balanced brackets: \n");
    scanf("%s", &check);
    printf("Your input is: %s\n", check);
    if (balanced(check))
        printf("Brackets are Balanced\n");
    else
        printf("Brackets are not Balanced\n");
    printf("\nThank you");
}
