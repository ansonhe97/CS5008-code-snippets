#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
}node_t;

typedef struct queue {
    node_t* head;
    node_t* tail;
    int size;
}queue_t;

queue_t* create_queue();
int size(queue_t* queue);
int peek(queue_t* queue);
void enqueue(queue_t* queue, int value);
int dequeue(queue_t* queue);
void destroy_queue(queue_t* queue);
void print_queue(queue_t* queue);

int main() {
    queue_t* queue = create_queue();
    enqueue(queue, 4);
    enqueue(queue, 7);
    enqueue(queue, 8);
    enqueue(queue, 10);
    printf("Queue: ");
    print_queue(queue);

    int popped = dequeue(queue);
    printf("Popped: %d\n", popped);
    printf("Update Queue: ");
    print_queue(queue);
    printf("Queue size: %d\n", size(queue));
    printf("Peek: %d\n", peek(queue));

    destroy_queue(queue);
    return 0;
}

queue_t* create_queue() {
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    if (queue == NULL) {
        return NULL;
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

int size(queue_t* queue) {
    if (queue == NULL) {
        return -1;
    }
    return queue->size;
}

int peek(queue_t* queue) {
    if (queue == NULL) {
        return -1;
    }
    return queue->head->value;
}

void enqueue(queue_t* queue, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        return;
    }
    new_node->next = NULL;
    new_node->value = value;

    if (queue->size == 0) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    queue->size++;
}

int dequeue(queue_t* queue) {
    if (queue == NULL) {
        return -1;
    }

    if (queue->size == 0) {
        return -1;
    }

    int value = queue->head->value;
    node_t* old_head = queue->head;

    if (queue->size == 1) {
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }

    free(old_head);
    queue->size--;
    return value;
}

void print_queue(queue_t* queue) {
    node_t* itr = queue->head;
    while (itr != NULL) {
        printf("%d ", itr->value);
        itr = itr->next;
    }
    printf("\n");
}

void destroy_queue(queue_t* queue) {
    node_t* itr = queue->head;
    while (itr != NULL) {
        node_t* temp = itr;
        itr = itr->next;
        free(temp);
    }
    free(queue);
}