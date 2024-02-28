/*
    Implementation of Min Binary Heap

    “parent(i)=(i-1)/2” for the parent node.
    “left_child(i)=2*i+1” for the left child.
    “right_child(i)=2*i+2” for the right child.
*/

#include <stdio.h>
#include <stdlib.h>

#define MIN_MAX -9999
#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

typedef struct min_heap {
    int* array;
    int size;
    int capacity;
}heap_t;

void swap(int* a, int* b);
heap_t* create_heap(int capacity);
void insert(heap_t* heap, int data);
void _insert_helper(heap_t* heap, int index);
void _resize_heap(heap_t* heap);
void heapify_min(heap_t* heap, int index);
int peek(heap_t* heap);
int extract_min(heap_t* heap);
void print_heap(heap_t* heap);
void destroy_heap(heap_t* heap);

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

heap_t* create_heap(int capacity) {
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
    if (heap == NULL)
        return NULL;
    heap->capacity = capacity;
    heap->size = 0;

    heap->array = (int*)malloc(sizeof(int) * capacity);
    if (heap->array == NULL)
        return NULL;
    for (int i=0; i<capacity; i++) {
        heap->array[i] = 0;
    }
    return heap;
}

void _insert_helper(heap_t* heap, int index) {
    // store parent at idx
    int parent = (index - 1) / 2;
    // swap if child is smaller than parent
    if (heap->array[parent] > heap->array[index]) {
        swap(&heap->array[parent], &heap->array[index]);
        // recursively call
        _insert_helper(heap, parent);
    }
}

void _resize_heap(heap_t* heap) {
    heap->capacity *= 2;
    heap->array = (int*)realloc(heap->array, heap->capacity * sizeof(int));
}

void insert(heap_t* heap, int data) {
    if (heap->size == heap->capacity) {
        _resize_heap(heap);
        DEBUG_PRINT("Resize heap->capacity to: %d\n", heap->capacity);
    }
    heap->array[heap->size] = data;
    _insert_helper(heap, heap->size);
    heap->size++;
}

void heapify_min(heap_t* heap, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    // check not out of bound
    if (left >= heap->size)
        left = -1;
    if (right >= heap->size)
        right = -1;

    // if left or right is smaller, store in min
    if (left != -1 && heap->array[left] < heap->array[min])
        min = left;
    if (right != -1 && heap->array[right] < heap->array[min])
        min = right;
    // this point min is the smallest out of the child

    if (min != index) {
        swap(&heap->array[min], &heap->array[index]);
        heapify_min(heap, min);
    }
}

int peak(heap_t* heap) {
    if (heap->size <= 0) {
        return MIN_MAX;
    }
    return heap->array[0];
}

int extract_min(heap_t* heap) {
    int delete;
    if (heap->size == 0)
        return MIN_MAX;

    delete = heap->array[0];
    // replace with last node
    heap->array[0] = heap->array[heap->size-1];
    heap->size--;
    heapify_min(heap, 0);
    return delete;
}

void print_heap(heap_t* heap) {
    for (int i=0; i<heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

void destroy_heap(heap_t* heap) {
    free(heap->array);
    free(heap);
}

int main() {
    heap_t* heap = create_heap(3);
    insert(heap, 10);
    insert(heap, 2);
    insert(heap, 8);
    insert(heap, 4);
    print_heap(heap);

    printf("Extract min: %d\n", extract_min(heap));
    print_heap(heap);
    printf("\n");

    insert(heap, 1);
    insert(heap, 7);
    insert(heap, 99);
    print_heap(heap);
    printf("Extract min: %d\n", extract_min(heap));
    print_heap(heap);

    destroy_heap(heap);
    return 0;
}

