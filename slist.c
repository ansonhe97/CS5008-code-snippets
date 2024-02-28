#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
}node_t;

typedef struct slist {
    node_t* head;
    node_t* tail;
    int size;
}slist_t;

void printNodes(node_t* node) {
    node_t* itr = node;

    while (itr != NULL) {
        printf("%d ", itr->data);
        itr = itr->next;
    }
    printf("\n");
}

node_t* makeNode(int data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL)
        return NULL;
    new_node->data = data;
    new_node->next = NULL; // initialize next to NULL
    return new_node;
}

void freeNode(node_t* node) {
    if (node == NULL)
        return;
    free(node);
}

slist_t* makeList() {
    slist_t* newList = (slist_t*)malloc(sizeof(slist_t));
    if (newList == NULL)
        return NULL;

    // clean gabage data
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

int push_front(slist_t* slist, int value) {
    if (slist == NULL)
        return 0;
    node_t* newNode = makeNode(value);
    if (newNode == NULL)
        return 0;
    
    // if list is empty
    if (slist->head == NULL) {
        slist->head = newNode;
        slist->tail = newNode;
    } else {
        // insert newNode before current head
        newNode->next = slist->head;
        slist->head = newNode;
    }
    slist->size++;
    return 1;
}

int push_back(slist_t* slist, int value) {
    if (slist == NULL)
        return 0;
    node_t* newNode = makeNode(value);
    if (newNode == NULL)
        return 0;
    if (slist->head == NULL) {
        slist->head = newNode;
        slist->tail = newNode;
    } else {
        slist->tail->next = newNode;    // 将新节点添加到链表的末尾
        slist->tail = newNode;          // 更新尾节点指针
    }
    slist->size++;
    return 1;
}

int insert(slist_t* slist, int pos, int value) {
    if (slist == NULL || pos < 0)
        return 0;

    if (pos == 0)
        return push_front(slist, value);
    
    if (pos >= slist->size)
        return push_back(slist, value);
    
    node_t* newNode = makeNode(value);
    if (newNode == NULL)
        return 0;

    // 检查插入的位置的前一个节点是否已经是尾部 
    node_t* itr = slist->head;
    for (int i=0; i<pos-1; i++) {
        if (itr->next == NULL) {
            free(newNode);
            return 0;
        }
        itr = itr->next;
    }
    // 遍历到插入点的前一个节点 所以现在itr在pos的前一个节点
    newNode->next = itr->next;
    itr->next = newNode;
    slist->size++;
    return 1;
}

void freeList(slist_t* worklist) {
    if (worklist == NULL)
        return;

    node_t* itr = worklist->head;
    node_t* next = NULL;

    while (itr != NULL) {
        next = itr->next;   // 保持下一个节点的地址
        free(itr);          // free当前节点
        itr = next;         // 移动到下一个节点
    }
    free(worklist);
}

int main() {
    /* 
    OLD VERSION USING NODES

    node_t* node1 = makeNode(1);
    node_t* node2 = makeNode(2);
    node_t* node3 = makeNode(3);

    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    printNodes(node1);

    free(node1);
    free(node2);
    free(node3);
    */
    slist_t* mylist = makeList();
    push_front(mylist, 3);
    push_front(mylist, 2);
    push_front(mylist, 1);
    printNodes(mylist->head);

    push_back(mylist, 4);
    push_back(mylist, 5);
    push_back(mylist, 6);

    printNodes(mylist->head);

    insert(mylist, 3, 1000);

    printNodes(mylist->head);
    freeList(mylist);


    return 0;
}