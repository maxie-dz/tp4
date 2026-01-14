#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct SNode {
    char data;
    struct SNode* next;
} SNode;

typedef struct QNode {
    char data;
    struct QNode* next;
} QNode;

typedef struct {
    QNode* front;
    QNode* rear;
} Queue;

SNode* push(SNode* top, char ch) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    newNode->data = ch;
    newNode->next = top;
    return newNode;
}

SNode* pop(SNode* top, char* ch) {
    if (top == NULL) return NULL;
    SNode* temp = top;
    *ch = top->data;
    top = top->next;
    free(temp);
    return top;
}

void enqueue(Queue* q, char ch) {
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    newNode->data = ch;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(Queue* q, char* ch) {
    if (q->front == NULL) return 0;
    QNode* temp = q->front;
    *ch = q->front->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return 1;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;

    SNode* stack = NULL;
    Queue queue = {NULL, NULL};

    for (int i = 0; str[i] != '\0'; i++) {
        char c = toupper(str[i]);
        if (isalpha(c)) {
            stack = push(stack, c);
            enqueue(&queue, c);
        }
    }

    int isPalindrome = 1;
    char c1, c2;

    while (stack != NULL && queue.front != NULL) {
        stack = pop(stack, &c1);
        dequeue(&queue, &c2);
        if (c1 != c2) {
            isPalindrome = 0;
            break;
        }
    }

    if (isPalindrome) printf("Palindrome\n");
    else printf("Not Palindrome\n");

    while (stack != NULL) {
        stack = pop(stack, &c1);
    }
    while (queue.front != NULL) {
        dequeue(&queue, &c1);
    }

    return 0;
}