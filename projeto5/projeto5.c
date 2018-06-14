#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct no {
    int value;
    struct no *left;
    struct no *right;
} No;

// Main functions
No *loadTreeFromFile(char* name_file); // Read file, create a tree, return the tree
void showTree(No* tree); // Show the tree
void isFull(No* tree); // Show if tree is full or not
void searchValue(No* tree, int term); // Show nv No, value of father and value of brother(if exist)
void getHeight(No* tree); // Show the height of the tree
void removeValue(No* tree, int term); // Remove value of the tree, if don't exist, warn the user
void printInOrder(No* tree); // Show tree in order
void printPreOrder(No* tree); // Show tree pre order
void printPostOrder(No* tree); // Show tree post order
void balanceTree(No* tree); // Check if the tree is balanced, if it's not, balance using rotation method
// Other functions
No *insert(No* tree, int value);
No *newNo(int term);
int getLevelUtil(No *tree, int term, int level);
int height(No *tree);
bool isFullTree(No* tree);


int main() {
    No *tree;
    char name_file[4];
    int status;
    int valueSearch;
    printf("Digite o nome do arquivo a ser aberto: ");
    scanf("%s", name_file);
    tree = loadTreeFromFile(name_file);

    do {
        printf("Escolha uma das opcoes seguintes:\n");
        printf("1 - Mostrar arvore\n");
        printf("2 - Mostrar se a arvore e cheia ou nao\n");
        printf("3 - Procurar um valor dentro da arvore\n");
        printf("4 - Mostrar a altura da arvore\n");
        printf("5 - Remover valor da arvore\n");
        printf("6 - Imprimir com o algoritmo In Order\n");
        printf("7 - Imprimir com o algoritmo Pre Order\n");
        printf("8 - Imprimir com o algoritmo Post Order\n");
        printf("9 - Balancear arvore\n");
        printf("10 - Sair\n");
        printf("Sua escolha: ");
        scanf("%d", &status);
        printf("\n");

        switch(status) {
            case 1:
                printf("Case 1\n");
                break;
            case 2:
                isFull(tree);
                break;
            case 3:
                printf("Digite o numero a ser procurado: ");
                scanf("%d", &valueSearch);
                searchValue(tree, valueSearch);
                break;
            case 4:
                getHeight(tree);
                break;
            case 5:
                printf("Case 5\n");
                break;
            case 6:
                printInOrder(tree);
                printf("\n");
                break;
            case 7:
                printPreOrder(tree);
                printf("\n");
                break;
            case 8:
                printPostOrder(tree);
                printf("\n");
                break;
            case 9:
                printf("Case 9\n");
                break;
            case 10:
                printf("Saindo...\n");
                break;
            default:
            printf("Opcao invalida, escolha uma opcao entre 1 e 10!\n");
                break;

        }
    } while(status != 10);

    return  0;
}

No *loadTreeFromFile(char* name_file) {
    No *tree = NULL;
    // createTree(tree);
    char *full_file_name = (char*) malloc(15*sizeof(char));
    sprintf(full_file_name, "./BSTs/%s.txt", name_file);
    FILE *file = fopen(full_file_name, "r+");
    if(file == NULL) {
        printf("Arquivo nao encontrado!!\n");
        exit(1);
    }

    char x;
    int *vetTree = (int*) malloc(10*sizeof(int));
    int y = 0, count = 0;
    char *aux = (char*) malloc(3*sizeof(char));

    do {
        fscanf(file, "%c", &x);
        if(x == ' ' || x == '\0') {
            y = 0;
            vetTree[count] = atoi(aux);
            memset(aux, ' ', 3);
            count++;
        } else {
            aux[y] = x;
            y++;
        }
    } while(count != 10);

    for(int i = 0; i<10; i++) {
        tree = insert(tree, vetTree[i]);
    }

    return tree;
}

void isFull(No* tree) {
    bool full = isFullTree(tree);
    if (full) {
        printf("A arvore e cheia\n\n\n");
    } else {
        printf("A arvore nao e cheia\n\n\n");
    }
}

void searchValue(No* tree, int term) {
    int level = getLevelUtil(tree, term, 1);
    if(level == 0) {
        printf("\nNumero nao encontrado!\n\n\n");
    } else {
        printf("\nO nivel do valor %d e %d\n\n\n", term, level);
    }
}

void getHeight(No *tree) {
    int n_height = height(tree);

    if(n_height == 0) {
        printf("Arvore vazia!\n");
    } else {
        printf("A arvore tem tamanho %d\n\n\n", n_height);
    }

}

/*void removeValue(No** tree, int term) {
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
} */

void printInOrder(No *no) {
    if(no != NULL) {
        printInOrder(no->left);
        printf("\n%d", no->value);
        printInOrder(no->right);
    }
}

void printPreOrder(No *no) {
    if(no != NULL) {
        printf("\n%d", no->value);
        printPreOrder(no->left);
        printPreOrder(no->right);
    }
}

void printPostOrder(No *no) {
    if(no != NULL) {
        printPostOrder(no->left);
        printPostOrder(no->right);
        printf("\n%d", no->value);
    }
}


No *newNo(int term) {
    No *temp = (No*) malloc(sizeof(No));
    temp->value = term;
    temp->left = temp->right = NULL;
    return temp;
}

No *insert(No* tree, int value) {
    if (tree == NULL) return newNo(value);

    if (value < tree->value) {
        tree->left = insert(tree->left, value);
    } else if (value > tree->value) {
        tree->right = insert(tree->right, value);
    }
    return tree;
}

int getLevelUtil(No *tree, int term, int level) {
    if (tree == NULL) {
        return 0;
    }
    if (tree->value == term) {
        return level;
    }

    int downlevel = getLevelUtil(tree->left, term, level+1);
    if (downlevel != 0) {
        return downlevel;
    }
    downlevel = getLevelUtil(tree->right, term, level+1);
    return downlevel;
}

int height(No *tree) {
    if (tree == NULL) {
        return 0;
    } else {
        int lH = height(tree->left);
        int rH = height(tree->right);

        if (lH > rH) {
            return (lH + 1);
        } else {
            return (rH + 1);
        }
    }
}

bool isFullTree(No* tree) {
    if (tree == NULL) {
        return true;
    }
    if (tree->left == NULL && tree->right == NULL) {
        return true;
    }
    if ((tree->left) && (tree->right)) {
        return (isFullTree(tree->left) && isFullTree(tree->right));
    }
    return false;
}