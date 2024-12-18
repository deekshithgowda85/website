#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CACHE_SIZE 10  // Cache capacity

// Structures
typedef struct AVLNode {
    int secondary_key;
    int primary_key;
    struct AVLNode *left, *right;
    int height;
} AVLNode;

typedef struct HashMap {
    int primary_key;
    char data[256];
    struct HashMap *next;
} HashMap;

typedef struct CacheEntry {
    int primary_key;
    char data[256];
    int access_time;
} CacheEntry;

// Global variables
CacheEntry cache[MAX_CACHE_SIZE];
int cache_size = 0;
int current_time = 0;

#define HASH_SIZE 100
HashMap *hash_table[HASH_SIZE] = {NULL};

// Function prototypes
int hash_function(int key);
HashMap* create_hash_entry(int primary_key, const char* data);
void insert_to_hash(int primary_key, const char* data);
char* search_in_hash(int primary_key);
void delete_from_hash(int primary_key);
void view_all_records();

AVLNode* create_avl_node(int primary_key, int secondary_key);
AVLNode* insert_to_avl(AVLNode* root, int primary_key, int secondary_key);
AVLNode* delete_from_avl(AVLNode* root, int secondary_key);
AVLNode* range_query(AVLNode* root, int start, int end);
AVLNode* min_value_node(AVLNode* node);

void put_to_cache(int primary_key, const char* data);
char* get_from_cache(int primary_key);
void evict_lru();
void view_cache();
int max(int a, int b);
int get_height(AVLNode* node);
AVLNode* rotate_right(AVLNode* y);
AVLNode* rotate_left(AVLNode* x);
int get_balance(AVLNode* node);

// HashMap Functions
int hash_function(int key) {
    return key % HASH_SIZE;
}

HashMap* create_hash_entry(int primary_key, const char* data) {
    HashMap* new_entry = (HashMap*)malloc(sizeof(HashMap));
    new_entry->primary_key = primary_key;
    strcpy(new_entry->data, data);
    new_entry->next = NULL;
    return new_entry;
}

void insert_to_hash(int primary_key, const char* data) {
    int index = hash_function(primary_key);
    HashMap* new_entry = create_hash_entry(primary_key, data);

    if (!hash_table[index]) {
        hash_table[index] = new_entry;
    } else {
        HashMap* temp = hash_table[index];
        while (temp->next) temp = temp->next;
        temp->next = new_entry;
    }
}

char* search_in_hash(int primary_key) {
    int index = hash_function(primary_key);
    HashMap* temp = hash_table[index];
    while (temp) {
        if (temp->primary_key == primary_key) return temp->data;
        temp = temp->next;
    }
    return NULL;  // Not found
}

void delete_from_hash(int primary_key) {
    int index = hash_function(primary_key);
    HashMap* temp = hash_table[index];
    HashMap* prev = NULL;

    while (temp) {
        if (temp->primary_key == primary_key) {
            if (prev) {
                prev->next = temp->next;
            } else {
                hash_table[index] = temp->next;
            }
            free(temp);
            printf("Record with Primary Key %d deleted from Hash.\n", primary_key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Record with Primary Key %d not found in Hash.\n", primary_key);
}

void view_all_records() {
    printf("\n--- All Records in Hash Table ---\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        HashMap* temp = hash_table[i];
        while (temp) {
            printf("Primary Key: %d, Data: %s\n", temp->primary_key, temp->data);
            temp = temp->next;
        }
    }
}

// AVL Tree Functions
AVLNode* create_avl_node(int primary_key, int secondary_key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->primary_key = primary_key;
    node->secondary_key = secondary_key;
    node->left = node->right = NULL;
    node->height = 1;  // New node starts at height 1
    return node;
}

int get_height(AVLNode* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;

    return x;
}

AVLNode* rotate_left(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

int get_balance(AVLNode* node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

AVLNode* insert_to_avl(AVLNode* root, int primary_key, int secondary_key) {
    if (!root) return create_avl_node(primary_key, secondary_key);

    if (secondary_key < root->secondary_key)
        root->left = insert_to_avl(root->left, primary_key, secondary_key);
    else if (secondary_key > root->secondary_key)
        root->right = insert_to_avl(root->right, primary_key, secondary_key);
    else
        return root;  // Duplicate secondary_key not allowed

    root->height = 1 + max(get_height(root->left), get_height(root->right));
    int balance = get_balance(root);

    if (balance > 1 && secondary_key < root->left->secondary_key)
        return rotate_right(root);
    if (balance < -1 && secondary_key > root->right->secondary_key)
        return rotate_left(root);
    if (balance > 1 && secondary_key > root->left->secondary_key) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && secondary_key < root->right->secondary_key) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

AVLNode* min_value_node(AVLNode* node) {
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

AVLNode* delete_from_avl(AVLNode* root, int secondary_key) {
    if (!root) return root;

    if (secondary_key < root->secondary_key)
        root->left = delete_from_avl(root->left, secondary_key);
    else if (secondary_key > root->secondary_key)
        root->right = delete_from_avl(root->right, secondary_key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            AVLNode* temp = min_value_node(root->right);
            root->secondary_key = temp->secondary_key;
            root->primary_key = temp->primary_key;
            root->right = delete_from_avl(root->right, temp->secondary_key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(get_height(root->left), get_height(root->right));
   int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0)
        return rotate_right(root);

    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0)
        return rotate_left(root);

    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

AVLNode* range_query(AVLNode* root, int start, int end) {
    if (!root) return NULL;

    if (root->secondary_key > end)
        return range_query(root->left, start, end);
    else if (root->secondary_key < start)
        return range_query(root->right, start, end);
    else {
        printf("Primary Key: %d, Secondary Key: %d\n", root->primary_key, root->secondary_key);
        range_query(root->left, start, end);
        range_query(root->right, start, end);
    }
    return root;
}

// Cache Functions
void put_to_cache(int primary_key, const char* data) {
    if (cache_size < MAX_CACHE_SIZE) {
        cache[cache_size].primary_key = primary_key;
        strcpy(cache[cache_size].data, data);
        cache[cache_size].access_time = current_time++;
        cache_size++;
    } else {
        evict_lru();
        put_to_cache(primary_key, data);
    }
}

void evict_lru() {
    int lru_index = 0;
    for (int i = 1; i < cache_size; i++) {
        if (cache[i].access_time < cache[lru_index].access_time)
            lru_index = i;
    }
    for (int i = lru_index; i < cache_size - 1; i++) {
        cache[i] = cache[i + 1];
    }
    cache_size--;
}

char* get_from_cache(int primary_key) {
    for (int i = 0; i < cache_size; i++) {
        if (cache[i].primary_key == primary_key) {
            cache[i].access_time = current_time++;
            return cache[i].data;
        }
    }
    return NULL;
}
// User Interface
void display_menu() {
    printf("\n--- Database System ---\n");
    printf("1. Insert Record\n");
    printf("2. Search by Primary Key\n");
    printf("3. Perform Range Query on Secondary Keys\n");
    printf("4. View Cache\n");
    printf("5. Delete Record\n");
    printf("6. View All Records\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}
void view_cache() {
    printf("\n--- Cache Contents ---\n");
    if (cache_size == 0) {
        printf("Cache is empty.\n");
        return;
    }
    for (int i = 0; i < cache_size; i++) {
        printf("Primary Key: %d, Data: %s, Access Time: %d\n", cache[i].primary_key, cache[i].data, cache[i].access_time);
    }
}

int main() {
    AVLNode* root = NULL;
    int choice, primary_key, secondary_key, start, end;
    char data[256];

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Primary Key: ");
                scanf("%d", &primary_key);
                printf("Enter Secondary Key: ");
                scanf("%d", &secondary_key);
                printf("Enter Data: ");
                scanf("%s", data);

                insert_to_hash(primary_key, data);
                root = insert_to_avl(root, primary_key, secondary_key);
                printf("Record inserted successfully.\n");
                break;

            case 2:
                printf("Enter Primary Key to Search: ");
                scanf("%d", &primary_key);

                char* cache_data = get_from_cache(primary_key);
                if (cache_data) {
                    printf("Cache Hit! Data: %s\n", cache_data);
                } else {
                    char* hash_data = search_in_hash(primary_key);
                    if (hash_data) {
                        printf("Cache Miss! Data: %s\n", hash_data);
                        put_to_cache(primary_key, hash_data);
                    } else {
                        printf("Record not found.\n");
                    }
                }
                break;

            case 3:
                printf("Enter Range Start (Secondary Key): ");
                scanf("%d", &start);
                printf("Enter Range End (Secondary Key): ");
                scanf("%d", &end);

                printf("Range Query Results:\n");
                range_query(root, start, end);
                break;

            case 4:
                view_cache();
                break;

            case 5:
                printf("Enter Primary Key to Delete: ");
                scanf("%d", &primary_key);
                printf("Enter Secondary Key to Delete: ");
                scanf("%d", &secondary_key);

                delete_from_hash(primary_key);
                root = delete_from_avl(root, secondary_key);
                break;

            case 6:
                view_all_records();
                break;

            case 7:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

