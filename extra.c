#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 1000   // max size of text buffer
#define MAX_SNAPSHOTS 50 // max number of snapshots allowed

// ============================
// Structure for a snapshot node (Queue)
// ============================
typedef struct Snapshot {
    char text[MAX_TEXT];
    struct Snapshot* next;
} Snapshot;

// Queue to store snapshots (FIFO)
typedef struct {
    Snapshot* front;
    Snapshot* rear;
    int size;
} SnapshotQueue;

// Stack to store undone snapshots (for redo maybe later)
typedef struct UndoNode {
    char text[MAX_TEXT];
    struct UndoNode* next;
} UndoNode;

// ============================
// Queue (Snapshot history) Functions
// ============================

// initialize queue
void initQueue(SnapshotQueue* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

// enqueue a snapshot
void enqueue(SnapshotQueue* q, const char* text) {
    Snapshot* newSnap = (Snapshot*)malloc(sizeof(Snapshot));
    strcpy(newSnap->text, text);
    newSnap->next = NULL;

    if (q->rear == NULL) { // first snapshot
        q->front = q->rear = newSnap;
    } else {
        q->rear->next = newSnap;
        q->rear = newSnap;
    }
    q->size++;
}

// dequeue last snapshot (for undo)
void dequeueLast(SnapshotQueue* q) {
    if (q->front == NULL) return; // nothing to remove

    // if only one snapshot
    if (q->front == q->rear) {
        free(q->front);
        q->front = q->rear = NULL;
    } else {
        Snapshot* temp = q->front;
        while (temp->next != q->rear)
            temp = temp->next;
        free(q->rear);
        q->rear = temp;
        q->rear->next = NULL;
    }
    q->size--;
}

// get the latest snapshot text
char* getCurrentText(SnapshotQueue* q) {
    if (q->rear == NULL)
        return "";
    return q->rear->text;
}

// ============================
// Stack Functions for Undo History
// (Not required but helps visualize undo storage)
// ============================

void pushUndo(UndoNode** top, const char* text) {
    UndoNode* newNode = (UndoNode*)malloc(sizeof(UndoNode));
    strcpy(newNode->text, text);
    newNode->next = *top;
    *top = newNode;
}

char* popUndo(UndoNode** top) {
    if (*top == NULL) return "";
    UndoNode* temp = *top;
    char* text = temp->text;
    *top = (*top)->next;
    return text;
}

// ============================
// Main Editor Functions
// ============================

void insertText(SnapshotQueue* q, const char* newText) {
    char buffer[MAX_TEXT];
    strcpy(buffer, getCurrentText(q)); // copy current
    strcat(buffer, newText);           // append new text
    enqueue(q, buffer);                // save as new snapshot
    printf("Inserted text: '%s'\n", newText);
}

void undoEdit(SnapshotQueue* q) {
    if (q->size <= 1) {
        printf("Nothing to undo!\n");
        return;
    }
    dequeueLast(q); // remove latest snapshot
    printf("Undo performed. Reverted to: \"%s\"\n", getCurrentText(q));
}

// ============================
// MAIN FUNCTION
// ============================
int main() {
    SnapshotQueue history;
    UndoNode* undoStack = NULL;
    initQueue(&history);

    // start with empty snapshot
    enqueue(&history, "");

    int choice;
    char input[MAX_TEXT];

    printf("=== Mini Text Editor (Insert + Undo) ===\n");
    printf("1. Insert Text\n");
    printf("2. Undo\n");
    printf("3. Show Current Text\n");
    printf("4. Exit\n");

    while (1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline from buffer

        switch (choice) {
            case 1:
                printf("Enter text to insert: ");
                fgets(input, MAX_TEXT, stdin);
                input[strcspn(input, "\n")] = '\0'; // remove newline
                insertText(&history, input);
                break;
            case 2:
                undoEdit(&history);
                break;
            case 3:
                printf("Current Text: \"%s\"\n", getCurrentText(&history));
                break;
            case 4:
                printf("Exiting editor.\n");
                exit(0);
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
