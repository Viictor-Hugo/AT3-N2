#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "hanoi.h"
#define MAX_DISKS 10

void initStack(Stack *stack, int capacity) {
    stack->disks = (int *)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
}

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int disk) {
    if (!isFull(stack)) {
        stack->disks[++stack->top] = disk;
    }
}

int pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->disks[stack->top--];
    }
    return -1;
}

void clearScreen() {
   
    printf("\033[H\033[J");
}

void display(Stack towers[], int numDisks, int moveCount) {
    clearScreen();
    printf("Numero de movimentos: %d\n", moveCount);
    for (int i = numDisks - 1; i >= 0; i--) {
        for (int t = 0; t < 3; t++) {
            if (i <= towers[t].top) {
                printf("  %d  ", towers[t].disks[i]);
            } else {
                printf("  |  ");
            }
        }
        printf("\n");
    }
    printf("==== ==== ====\n");
    printf("  1    2    3  \n\n");
}

void moveDisk(Stack towers[], int from, int to, int *moveCount) {
    if (isEmpty(&towers[from])) {
        printf("A torre %d esta vazia!\n", from + 1);
        sleep(2);
        return;
    }

    int disk = pop(&towers[from]);
    if (!isEmpty(&towers[to]) && towers[to].disks[towers[to].top] < disk) {
        printf("Nao e possivel colocar um disco maior sobre um menor.\n");
        push(&towers[from], disk); 
        sleep(2);
    } else {
        push(&towers[to], disk);
        (*moveCount)++;
    }
}

void resetGame(Stack towers[], int numDisks, int *moveCount) {
    for (int i = 0; i < 3; i++) {
        towers[i].top = -1;
    }
    for (int i = numDisks; i > 0; i--) {
        push(&towers[0], i);
    }
    *moveCount = 0;
}

void freeStacks(Stack towers[]) {
    for (int i = 0; i < 3; i++) {
        free(towers[i].disks);
    }
}

int checkVictory(Stack towers[], int numDisks) {
    return towers[2].top == numDisks - 1;
}

int main() {
    int numDisks;
    printf("Digite o numero de discos: ");
    scanf("%d", &numDisks);
    
    while (numDisks < 1 || numDisks > MAX_DISKS) {
        printf("Numero invalido. Digite um numero de discos entre 1 e %d: ", MAX_DISKS);
        scanf("%d", &numDisks);
    }

    Stack towers[3];
    for (int i = 0; i < 3; i++) {
        initStack(&towers[i], numDisks);
    }

    int moveCount = 0;
    resetGame(towers, numDisks, &moveCount);
    display(towers, numDisks, moveCount);

    int choice;
    while (1) {
        printf("Escolha uma opcao:\n");
        printf("1. Mover disco\n");
        printf("2. Reiniciar o jogo\n");
        printf("3. Desistir\n");
        scanf("%d", &choice);

        if (choice == 1) {
            int from, to;
            printf("Mover disco de qual torre 1, 2 ou 3? ");
            scanf("%d", &from);
            printf("Para qual torre 1, 2 ou 3? ");
            scanf("%d", &to);
            if (from < 1 || from > 3 || to < 1 || to > 3) {
                printf("Torre invalida. Tente novamente.\n");
                sleep(2);
            } else {
                moveDisk(towers, from - 1, to - 1, &moveCount);
                display(towers, numDisks, moveCount);
                if (checkVictory(towers, numDisks)) {
                    printf("Parabens! Voce venceu o jogo em %d movimentos.\n", moveCount);
                    break;
                }
            }
        } else if (choice == 2) {
            resetGame(towers, numDisks, &moveCount);
            display(towers, numDisks, moveCount);
        } else if (choice == 3) {
            printf("Voce desistiu.\n");
            break;
        } else {
            printf("Opcao invalida. Tente novamente.\n");
            sleep(2);
        }
    }

    freeStacks(towers);
    return 0;
}
