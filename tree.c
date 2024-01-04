#include <stdio.h>
#include <stdlib.h>

struct node {
   int data; 
   struct node *leftChild;
   struct node *rightChild;
};

struct node *root = NULL;

void insert(int data) {
   struct node *value = (struct node*) malloc(sizeof(struct node));
   struct node *current;
   struct node *parent;

   value->data = data;
   value->leftChild = NULL;
   value->rightChild = NULL;

   //if tree is empty
   if(root == NULL) {
      root = value;
   } else {
      current = root;
      parent = NULL;

      while(1) { 
         parent = current;
         if(data < parent->data) {  //LHS
            current = current->leftChild;                
            if(current == NULL) {   //insert to the left
               parent->leftChild = value;
               return;
            }
         }  //go to right of the tree
         else {                     //RHS
            current = current->rightChild;
            if(current == NULL) {   //insert to the right
               parent->rightChild = value;
               return;
            }
         }
      }            
   }
}

void pre_order_traversal(struct node* root) {
   if(root != NULL) {
      printf("%d ",root->data);
      pre_order_traversal(root->leftChild);
      pre_order_traversal(root->rightChild);
   }
}

void inorder_traversal(struct node* root) {
   if(root != NULL) {
      inorder_traversal(root->leftChild);
      printf("%d ",root->data);          
      inorder_traversal(root->rightChild);
   }
}

void post_order_traversal(struct node* root) {
   if(root != NULL) {
      post_order_traversal(root->leftChild);
      post_order_traversal(root->rightChild);
      printf("%d ", root->data);
   }
}

int main() {

   printf("\nHie, this program returns Inorder, Preorder and Postorder traversal of binary tree, for given array: ");

//    int array[7] = { 27, 14, 35, 10, 19, 31, 42 };
   // int array[7] = { 4 ,2 ,5, 1, 3 ,8 ,6};
   int input[10] = {4,2,7,5,8,1,3,9,6};

   for(int cnt = 0; cnt < 9; cnt++)
      insert(input[cnt]);

   printf("\nPreorder traversal looks like: ");
   pre_order_traversal(root);

   printf("\nInorder traversal looks like: ");
   inorder_traversal(root);

   printf("\nPost order traversal looks like: ");
   post_order_traversal(root);       

   printf("\n\nthanks!\tkeep smiling!\n");
}