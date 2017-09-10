#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WORD_LENGTH 10
#define LINE_LENGTH 23 /* word + space + word + newline + null */

struct node {
    char* key; 
    char* value;
    struct node* parent;
    struct node* low;
    struct node* high;
    long unsigned prio;
};

struct node* create(struct node* parent, char* key, char* value) {
    struct node* n = malloc(sizeof(struct node));

    n->key = malloc(sizeof(char)*(strlen(key)+1));
    n->value = malloc(sizeof(char)*(strlen(value)+1));
    strcpy(n->key, key);
    strcpy(n->value, value);

    n->parent = parent;
    n->low = NULL;
    n->high = NULL;
    n->prio = rand();

    return n;
}
void destroy(struct node* n) {
    if (n != NULL) {
        destroy(n->low);
        destroy(n->high);

        free(n->key);
        free(n->value);
        free(n);
    }
}
/*
 * Rotate n and return if it became root
 */
bool rotate(struct node* n) {
    struct node* parent = n->parent;

    if (parent->parent) {
        if (parent == parent->parent->low) {
            parent->parent->low = n;
        } else {
            parent->parent->high = n;
        }
    }

    if (n == parent->low) {
        /* rotate right */
        if (n->high) n->high->parent = parent;
        parent->low = n->high;
        n->high = parent;
    } else {
        /* rotate left */
        if (n->low) n->low->parent = parent;
        parent->high = n->low;
        n->low = parent;
    }

    n->parent = parent->parent;
    parent->parent = n;

    return n->parent == NULL;
}
/*
 * rotates n until it is root or has higher priority than
 * its parent. returns root
 * n may not be root at start
 */
struct node* order(struct node* n, struct node* root) {
    while (n->prio < n->parent->prio) {
        if (rotate(n)) return n;
    }

    return root;
}
/*
 * Insert value into treap (balanced binary search tree)
 * returns root node (NULL input node will create new)
 *
 * clientside:
 *  tree = insert(tree, key, value);
 */
struct node* insert(struct node* root, char* key, char* value) {
    if (root == NULL) {
        return create(NULL, key, value);
    }

    struct node* n = root;
    while (1) {
        int comp = strcmp(key, n->key);
        if (comp < 0) {
            if (n->low) {
                n = n->low;
            } else {
                struct node* next = create(n, key, value);
                n->low = next;
                return order(next, root);
            }
        } else if (comp > 0 ) {
            if (n->high) {
                n = n->high;
            } else {
                struct node* next = create(n, key, value);
                n->high = next;
                return order(next, root);
            }
        } else {
            return root;
        }
    }
}

/*
 * returns value for matching key if it exists,
 * otherwise null
 */
char* search(struct node* n, char* key) {
    while (1) {
        int comp = strcmp(key, n->key);
        if (comp < 0) {
            if (n->low) {
                n = n->low;
            } else {
                return NULL;
            }
        } else if (comp > 0) {
            if (n->high) {
                n = n->high;
            } else {
                return NULL;
            }
        } else {
            return n->value;
        }
    }

    return NULL;
}

/*
 * Algorithm:
 *  -insert entries into sorted binary tree (foreign as key, eng as value)
 *  -search tree for english with foreign key
 *  -??
 *  -profit
 */
int main() {
    struct node* dictionary = NULL;

    char buffer[LINE_LENGTH];
    while (fgets(buffer, LINE_LENGTH, stdin)[0] != '\n') {
        char* english = strtok(buffer, " ");
        char* foreign = strtok(NULL, "\n");
        dictionary = insert(dictionary, foreign, english);
    }

    char foreign_buffer[WORD_LENGTH+1];
    while (scanf("%s\n", foreign_buffer) == 1) {
        char* word_eng = search(dictionary, foreign_buffer);
        if (word_eng != NULL) {
            printf("%s\n", word_eng);
        } else {
            printf("eh\n");
        }
    }

    destroy(dictionary);
    
    return 0;
}
