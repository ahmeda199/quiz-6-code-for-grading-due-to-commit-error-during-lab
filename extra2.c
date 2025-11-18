#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Queue {

} Queue;

// Queue functions

}

int isEmpty(Queue* q) {
    return q->front > q->rear;
}

void enqueue(Queue* q, int value) {
    if (q->rear < MAX - 1) {
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    if (!isEmpty(q)) {
        int val = q->items[q->front];
        q->front++;
        return val;
    }
    return -1; // Queue empty
}

// BFS function
void bfs(int graph[MAX][MAX], int n, int start) {
    int visited[MAX] = {0};
    Queue q;
    initQueue(&q);

    // TODO


    while (!isEmpty(&q)) {
        // TODO
// visit it and then place it into queue // and print it
        // TODO
        // TODO

    }
}

int main() {
    int n = 6;
    int graph[MAX][MAX] = {0};

    // Example graph
    graph[0][1] = 1; graph[0][2] = 1;
    graph[1][0] = 1; graph[1][3] = 1; graph[1][4] = 1;
    graph[2][0] = 1; graph[2][5] = 1;
    graph[3][1] = 1;
    graph[4][1] = 1; graph[4][5] = 1;
    graph[5][2] = 1; graph[5][4] = 1;

// TODO Run it

    return 0;
}

// expected output:
// BFS starting from node 0:
// 0 1 2 3 4 5
﻿
 
 
