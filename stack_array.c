#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Stack {
    int *stack_array;
    int capacity;
    int size;
}mystack_t;

mystack_t* create_stack(int capacity);
void destroy_stack(mystack_t *stack);
bool is_full(mystack_t* stack);
bool is_empty(mystack_t* stack);
bool pop(mystack_t* stack, int* item);
bool push(mystack_t* stack, int item);
bool peek(mystack_t* stack, int* item);

mystack_t* create_stack(int capacity) {
    if (capacity <= 0) return NULL;

    mystack_t* stack = (mystack_t*)malloc(sizeof(mystack_t));
    if (stack == NULL) return NULL;

    stack->stack_array = malloc(sizeof(int) * capacity);
    if (stack->stack_array == NULL) {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->size = 0;
    return stack;
}

bool is_full(mystack_t* stack) {
    return stack->size == stack->capacity;
}

bool is_empty(mystack_t* stack) {
    return stack->size == 0;
}

bool push(mystack_t* stack, int item) {
    if (is_full(stack)) return false;

    stack->stack_array[stack->size] = item;
    stack->size++;
    return true;
}

bool peek(mystack_t* stack, int* item) {
    if (is_empty(stack)) return false;

    *item = stack->stack_array[stack->size-1];
    return true;
}

bool pop(mystack_t* stack, int* item) {
    if (is_empty(stack)) return false;

    stack->size--;
    *item = stack->stack_array[stack->size];

    return true;
}

void destroy_stack(mystack_t *stack) {
    free(stack->stack_array);
    free(stack);
}

int main() {
    mystack_t* stack = create_stack(5);
    push(stack, 5);
    push(stack, 2);
    push(stack, 1);
    printf("Stack size: %d\n", stack->size);
    push(stack, -1);
    push(stack, 7);
    printf("Stack size: %d\n", stack->size);
    if (!push(stack, 0)) printf("full!\n");

    int peek_val;
    peek(stack, &peek_val);
    printf("peek: %d\n", peek_val);

    int pop_val;
    for (int i=0; i<5; i++) {
        pop(stack, &pop_val);
        printf("pop: %d\n", pop_val);
    }

    if (is_empty(stack)) printf("Empty!\n");
    int test_peek;
    if (!peek(stack, &test_peek)) printf("Peek failed!\n");

    destroy_stack(stack);
    return 0;
}