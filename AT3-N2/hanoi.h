#ifndef HANOI_H
#define HANOI_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *disks;
    int top;
    int capacity;
} Stack;

void initStack(Stack *stack, int capacity);
int isFull(Stack *stack);
int isEmpty(Stack *stack);
void push(Stack *stack, int disk);
int pop(Stack *stack);
void display(Stack towers[], int numDisks, int moveCount);
void moveDisk(Stack towers[], int from, int to, int *moveCount);
void resetGame(Stack towers[], int numDisks, int *moveCount);
void freeStacks(Stack towers[]);
int checkVictory(Stack towers[], int numDisks);

#endif
