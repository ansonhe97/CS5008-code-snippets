#include <stdio.h>
#include <stdlib.h>

typedef struct vector {
    int* data;  // array
    int size;
    int capacity;
}vector_t;

vector_t* makeVector(int initial_capacity) {
    vector_t* vector = (vector_t*)malloc(sizeof(vector_t));
    if (vector==NULL) {
        return NULL;
    }
    // allocate memory for data array
    vector->data = (int*)malloc(sizeof(int)*initial_capacity);
        if (vector->data == NULL) {
        return NULL;
    }
    vector->size = 0;
    vector->capacity = initial_capacity;
    return vector;
}

void freeVector(vector_t* vector) {
    if (vector == NULL)
        return;
    // frist free data array
    if (vector->data != NULL) {
        free(vector->data);
    }
    free(vector);
}

int resize(vector_t* vector) {
    if (vector == NULL)
        return 0;
    vector->capacity = vector->capacity * 2;
    int* newData = (int*)malloc(sizeof(vector->capacity));
    if (newData == NULL || vector->data == NULL)
        return 0;
    // copy to new array
    for (int i=0; i<vector->size; i++) {
        newData[i] = vector->data[i];
    }
    free(vector->data); // free old array
    vector->data = newData;
    return 1;
}

int push_back(vector_t* vector, int element) {
    if (vector == NULL)
        return 0;
    
    if (vector->data == NULL)
        return 0;
    // check to ensure we have enough room, do we need to resize
    if (vector->size == vector->capacity) {
        int resizeSuccess = resize(vector);
        if (resizeSuccess == 0)
            return 0;
    }
    // e.g cap of 2, current size of 0, 1st time insert at 0, then size++, 2nd time insert at 1
    vector->data[vector->size] = element;
    vector->size += 1;
    return 1;
}

void print(vector_t* vector) {
    if (vector == NULL)
        return;
    if (vector->data == NULL)
        return;

    for (int i=0; i<vector->size; i++) {
        printf("%d ", vector->data[i]);
    }
    printf("\n");
}

int insert(vector_t* vector, int pos, int element) {
    if (vector == NULL || pos < 0)
        return 0;
    // if inserting at the end eg. current size of 1 and inserting at 1
    if (pos == vector->size) {
        return push_back(vector, element);
    }

    if (vector->size == vector->capacity) {
        int resizeSuccess = resize(vector);
        if (resizeSuccess == 0)
            return 0;
    }
    if (vector->data == NULL)
        return 0;
    
    // eg. size of 4, insert at idx 2, start from idx 3 ~ 2
    // [1 2 _ 3 4 _ ]

    for (int i=vector->size-1; i>=pos; i--) {
        vector->data[i+1] = vector->data[i];
    }

    vector->data[pos] = element;
    vector->size += 1;
    return 1;
}

int push_front(vector_t* vector, int element) {
    return insert(vector, 0, element);
}

int main() {
    vector_t* vector = makeVector(2);
    push_back(vector, 2);
    push_back(vector, 3);
    push_back(vector, 4);
    print(vector);

    push_front(vector, 1);
    push_front(vector, 0);
    print(vector);
    freeVector(vector);
    return 0;
}