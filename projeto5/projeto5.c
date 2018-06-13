#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int value;
    struct no *left;
    struct no *right;
} No;

// Main functions
No **loadTreeFromFile(char* name_file); // Read file, create a tree, return the tree
void showTree(No** tree); // Show the tree
void isFull(No** tree); // Show if tree is full or not
void searchValue(No** tree, int term); // Show nv No, value of father and value of brother(if exist)
void getHeight(No** tree); // Show the height of the tree
void removeValue(No** tree, int term); // Remove value of the tree, if don't exist, warn the user
void printInOrder(No** tree); // Show tree in order
void printPreOrder(No** tree); // Show tree pre order
void printPostOrder(No** tree); // Show tree post order
void balanceTree(No** tree); // Check if the tree is balanced, if it's not, balance using rotation method
// Other functions
void addValue(No** tree, int value);
No *higherRight(No** no);
No *higherLeft(No** no);

int main() {

    return  0;
}

No **loadTreeFromFile(char* name_file) {

}

void removeValue(No** tree, int term) {
    if(*tree == NULL) {
        printf("Este numero nao esta presente na arvore!\n");
        return;
    }
    if(term < (*tree)->value) {
        removeValue(&((*tree)->right), term);
    } else {
        if(term > (*tree)->value) {
            removeValue(&((*tree)->right), term);
        } else {
            No *aux = *tree;
            if(((*tree)->left) == NULL && ((*tree)->right == NULL)) {
                free(aux);
                (*tree) = NULL;
            } else {
                if((*tree)->left == NULL) {
                    (*tree) =(*tree)->right;
                    aux->right = NULL;
                    free(aux); aux = NULL;
                } else {
                    if((*tree)->right == NULL) {
                        (*tree) = (*tree)->left;
                        aux->left = NULL;
                        free(aux); aux = NULL;
                    } else {
                        aux = higherRight(&(*tree)->left);
                        aux->left = (*tree)->left;
                        aux->right = (*tree)->right;
                        (*tree)->left = (*tree)->right = NULL;
                        free((*tree)); *tree = aux; aux = NULL;
                    }
                }
            }
        }
    }
}

void addValue(No** tree, int value) {
    if(*tree == NULL) {
        *tree = (No*) malloc(sizeof(No));
        (*tree)->right = NULL;
        (*tree)->left = NULL;
        (*tree)->value = value;
    } else {
        if(value > ((*tree)->value)) {
            addValue(&((*tree)->right), value);
        } else {
            addValue(&((*tree)->left), value);
        }
    }
}

No *higherRight(No** no) {
    if((*no)->right != NULL) {
        return higherRight(&(*no)->right);
    } else {
        No *aux = *no;
        if((*no)->left != NULL) {
            *no = (*no)->left;
        } else {
            *no = NULL;
        }
        return aux;
    }
}

No *higherLeft(No** no) {
    if((*no)->left != NULL) {
        return higherLeft(&(*no)->left);
    } else {
        No *aux = *no;
        if((*no)->right != NULL) {
            *no = (*no)->right;
        } else {
            *no = NULL;
        }
        return aux;
    }
}