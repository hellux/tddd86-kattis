#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* max values for lazy memory allocation */
#define WORDS 100000
#define WORD_LENGTH 10
#define LINE_LENGTH 23 /* word + space + word + newline + null */

struct node {
    char* key; 
    char* value;
    struct node* low;
    struct node* high;
};

struct node* create(char* key, char* value) {
    struct node* n = malloc(sizeof(struct node));
    n->key = key;
    n->value = value;
    n->low = NULL;
    n->high = NULL;

    return n;
}
/*
 * Insert value to binary tree
 * returns root node (NULL input node will create new)
 *
 * clientside:
 *  tree = insert(tree, key, value);
 */
struct node* insert(struct node* root, char* key, char* value) {
    if (root == NULL) {
        return create(key, value);
    }

    struct node* n = root;
    while (1) {
        fflush(stdout);
        if (strcmp(key, n->key) < 0) {
            if (n->low) {
                n = n->low;
            } else {
                struct node* next = create(key, value);
                n->low = next;
                break;
            }
        } else {
            if (n->high) {
                n = n->high;
            } else {
                struct node* next = create(key, value);
                n->high = next;
                break;
            }
        } /* do not handle equal keys */
    }

    return root;
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
 *  -insert entries into sorted binary tree
 *  -search tree
 */
int main() {
    char english[WORDS][WORD_LENGTH+1];
    char foreign[WORDS][WORD_LENGTH+1];
    struct node* dictionary = NULL;

    int index = 0;
    char buffer[LINE_LENGTH];
    while (fgets(buffer, LINE_LENGTH, stdin)[0] != '\n') {
        strcpy(english[index], strtok(buffer, " "));
        strcpy(foreign[index], strtok(NULL, "\n"));
        dictionary = insert(dictionary, foreign[index], english[index]);
        index++;
    }

    char foreign_buffer[WORD_LENGTH+1];
    while (scanf("%s\n", foreign_buffer) == 1) {
        fflush(stdout);
        char* word_eng = search(dictionary, foreign_buffer);
        if (word_eng != NULL) {
            printf("%s\n", word_eng);
        } else {
            printf("eh\n");
        }
    }
    
    return 0;
}
