#ifndef QUEUE
#define QUEUE
#define MAX_SIZE 2000

struct QNode {
    int key;
    struct QNode* next;
};

struct Queue {
    struct QNode *front, *rear;
};
struct QNode* newNode(int k);
struct Queue* createQueue();//creates empty queue

void enQueue(struct Queue* q, int k);

void deQueue(struct Queue* q);

void done(struct Queue* q);//clears the queue

int count(struct Queue *q);

bool IsItEmpty(struct Queue *q); // if the queue is empty returns true, if not - false

void make_empty(struct Queue *q);// fills queue with 0 values

int count_with_zeros(struct Queue *q);

void print(struct Queue *q);

void clone (struct Queue *q, struct Queue *a);
#endif