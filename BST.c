#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

typedef struct treenode {
    int value;
    struct treenode* left, *right;
}treenode_t;

typedef struct queuenode {
    treenode_t* treenode;
    struct queuenode* next;
}queuenode_t;

typedef struct queue {
    queuenode_t* front, *rear;
}queue_t;

treenode_t* create_node(int value);
treenode_t* search_node(treenode_t* root, int target);
treenode_t* insert_node(treenode_t* node, int value);
void pre_order_traversal(treenode_t* root);
void in_order_traversal(treenode_t* root);
void post_order_traversal(treenode_t* root);
treenode_t* find_min(treenode_t* root);
treenode_t* delete_node(treenode_t* root, int value);
void delete_tree(treenode_t* root);

/**
 * Queue Implementation
*/
queue_t* create_queue() {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    if (!q) return NULL;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue(queue_t* q, treenode_t* treenode) {
    queuenode_t* new_node = (queuenode_t*)malloc(sizeof(queuenode_t));
    if (!new_node) return;
    new_node->treenode = treenode;
    new_node->next = NULL;
    if (q->rear == NULL) {
        q->front = new_node;
        q->rear = new_node;
    } else {
    q->rear->next = new_node;
    q->rear = new_node;
    }
}

treenode_t* dequeue(queue_t* q) {
    if (!q) return NULL;
    if (q->front == NULL) return NULL;
    queuenode_t* temp = q->front;
    treenode_t* result = temp->treenode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return result;
}

int is_queue_empty(queue_t* q) {
    return q->front == NULL;
}

void delete_queue(queue_t* q) {
    while (!is_queue_empty(q)) {
        dequeue(q);
    }
    free(q);
}

void BFS_level_order_traversal(treenode_t* root) {
    if (!root) return;
    queue_t* q = create_queue();
    enqueue(q, root);
    while (!is_queue_empty(q)) {
        treenode_t* current_node = dequeue(q);
        printf("%d ", current_node->value);

        // left to right
        if (current_node->left)
            enqueue(q, current_node->left);
        if (current_node->right)
            enqueue(q, current_node->right);
    }
    delete_queue(q);
}

treenode_t* create_node(int value) {
    treenode_t* new_node = (treenode_t*)malloc(sizeof(treenode_t));
    if (new_node == NULL)
        return NULL;
    new_node->value = value;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

treenode_t* search_node(treenode_t* root, int target) {
    if (root == NULL || root->value == target)
        return root;
    if (target < root->value) {
        return search_node(root->left, target);
    } else {
        return search_node(root->right, target);
    }
}

treenode_t* insert_node(treenode_t* node, int value) {
    if (node == NULL) {
        return create_node(value);
    }

    if (value < node->value) {
        node->left = insert_node(node->left, value);
    } else if (value > node->value) {
        node->right = insert_node(node->right, value);
    }

    return node;
}

void pre_order_traversal(treenode_t* root) {
    if (root != NULL) {
        printf(" %d", root->value);
        pre_order_traversal(root->left);
        pre_order_traversal(root->right);
    }
}

void in_order_traversal(treenode_t* root) {
    if (root!= NULL) {
        in_order_traversal(root->left);
        printf(" %d", root->value);
        in_order_traversal(root->right);
    }
}

void post_order_traversal(treenode_t* root) {
    if (root!= NULL) {
        post_order_traversal(root->left);
        post_order_traversal(root->right);
        printf(" %d", root->value);
    }
}

treenode_t* find_min(treenode_t* root) {
    if (root == NULL) return NULL;
    if (root->left != NULL) {
        return find_min(root->left);
    }
    return root;
}

treenode_t* delete_node(treenode_t* root, int value) {
    if (root == NULL) return NULL;

    if (value < root->value) {
        DEBUG_PRINT(" [delete] searching root value: %d\n", root->value);
        root->left = delete_node(root->left, value);
    } else if (value < root->value) {
        DEBUG_PRINT(" [delete] searching root value: %d\n", root->value);
        root->right = delete_node(root->right, value);
    } else {
        // 找到了要删除的节点，并且该节点有两个子节点
        if (root->left != NULL && root->right != NULL) {
            DEBUG_PRINT(" [delete]-2 found root value: %d\n", root->value);
            treenode_t* temp = find_min(root->right);                //  找到中序后继，右子树最小的
            DEBUG_PRINT(" [delete]-2 in-order successor: %d\n", temp->value);
            root->value = temp->value;                               //  用中序后继的值替换当前节点的值
            root->right = delete_node(root->right, temp->value);     //  因为已经替换了，在右子树删除原来的中序后继
        } else {
            // 节点只有一个子节点或者叶子结点
            DEBUG_PRINT(" [delete]-1 found root value: %d\n", root->value);
            treenode_t* temp = root;
            if (root->left == NULL) {
                root = root->right;
            } else if (root->right == NULL) {
                root = root->left;
            }
            free(temp);
        }
    }
    return root;
}

void delete_tree(treenode_t* root) {
    if (root == NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

int main() {
    treenode_t* root = create_node(50);
    insert_node(root, 30);
    insert_node(root, 20);
    insert_node(root, 40);
    insert_node(root, 60);
    insert_node(root, 70);
    insert_node(root, 80);

    printf("Traversal: ");
    // pre_order_traversal(root);
    in_order_traversal(root);
    // pre_order_traversal(root);

    printf("\nMinimum value: %d\n", find_min(root)->value);

    printf("Searched 70: %d\n", search_node(root, 70)->value);
    if (search_node(root, 90) == NULL)
        printf("Not found 90\n");

    delete_node(root, 30);
    in_order_traversal(root);

    printf("\nBFS: ");
    BFS_level_order_traversal(root);

    delete_tree(root);
    return 0;
}