#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct SNode {
    char data;
    struct SNode *next;
} SNode;

typedef struct QNode {
    char data;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front;
    QNode *rear;
} Queue;

SNode* push(SNode *top, char c) {
    SNode *n = malloc(sizeof(SNode));
    n->data = c;
    n->next = top;
    return n;
}

SNode* pop(SNode *top, char *c) {
    SNode *t = top;
    *c = t->data;
    top = t->next;
    free(t);
    return top;
}

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue *q, char c) {
    QNode *n = malloc(sizeof(QNode));
    n->data = c;
    n->next = NULL;

    if (!q->rear)
        q->front = q->rear = n;
    else {
        q->rear->next = n;
        q->rear = n;
    }
}

int dequeue(Queue *q, char *c) {
    if (!q->front) return 0;

    QNode *t = q->front;
    *c = t->data;
    q->front = t->next;
    if (!q->front) q->rear = NULL;
    free(t);
    return 1;
}

int main() {
    char str[200], a, b;
    SNode *top = NULL;
    Queue q;

    initQueue(&q);
    fgets(str, sizeof(str), stdin);

    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i])) {
            char c = toupper(str[i]);
            top = push(top, c);
            enqueue(&q, c);
        }
    }

    while (top && q.front) {
        top = pop(top, &a);
        dequeue(&q, &b);
        if (a != b) {
            printf("Not Palindrome\n");
            return 0;
        }
    }

    printf("Palindrome\n");
    return 0;
}