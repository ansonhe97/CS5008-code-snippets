#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pair {
    char* key;
    int value;
}pair_t;

typedef struct node {
    struct node* next;
    pair_t* kv;
}node_t;

int stringHash(char* myKey, int numberOfBukcets) {
    return strlen(myKey) % numberOfBukcets;
}

typedef int(*hashFunctionPointer)(char*, int);

typedef struct hashmap {
    int buckets;
    node_t** arrayOfList;   // array of node_t* e.g. [node_t*, node_t* ...]
    hashFunctionPointer hashFunction;
}hashmap_t;

hashmap_t* hashmap_create(int _buckets) {
    hashmap_t* map = (hashmap_t*)malloc(sizeof(hashmap_t));

    map->buckets = _buckets;
    map->arrayOfList = (node_t**)malloc(sizeof(node_t*) * _buckets);

    for (int i=0; i<_buckets; i++)
        map->arrayOfList[i] = NULL;

    map->hashFunction = stringHash;

    return map;
}

void hashmap_insert(hashmap_t* in, char* key_in, int value) {
    pair_t* newpair = (pair_t*)malloc(sizeof(pair_t));
    newpair->key = (char*)malloc(sizeof(strlen(key_in)*sizeof(char)+1));
    newpair->value = value;
    strcpy(newpair->key, key_in);

    node_t* newnode = (node_t*)malloc(sizeof(node_t));
    newnode->next = NULL;
    newnode->kv = newpair;

    // determine which bucket to put in
    unsigned int bucket = in->hashFunction(key_in, in->buckets);

    // [_ bucket _ _ _ ]
    //  0   1    2 3 4
    if (in->arrayOfList[bucket] == NULL) {
        in->arrayOfList[bucket] = newnode;
    } else {
        // 把旧的node放到next 新的node放到前面
        // prepending
        newnode->next = in->arrayOfList[bucket];
        in->arrayOfList[bucket] = newnode;
    }
}

void hashmap_printKeyValues(hashmap_t* in) {
    for (int i=0; i<in->buckets; i++) {
        printf("Bucket# %d\n", i);
        node_t* itr = in->arrayOfList[i];
        while(itr != NULL) {
            printf("\tKey: %s\tValue: %d\n", itr->kv->key, itr->kv->value);
            itr = itr->next;
        }
    }
}

void hashmap_free(hashmap_t* in) {
    for (int i=0; i<in->buckets; i++) {
        node_t* itr = in->arrayOfList[i];
        while (itr != NULL) {
            node_t* next = itr->next;

            free(itr->kv->key);
            free(itr->kv);
            free(itr);

            itr = next;
        }
    }

    free(in->arrayOfList);
    free(in);
}

int main() {
    hashmap_t* map = hashmap_create(8);
    hashmap_insert(map, "Anson", 1);
    hashmap_insert(map, "Mike", 5);
    hashmap_insert(map, "Juancho", 12);
    hashmap_insert(map, "Logan A", 2);

    hashmap_printKeyValues(map);
    hashmap_free(map);
    return 0;
}