/*
 * Algorithm
 * -Calculate depth of all sub nodes before rotations
 * -Traverse tree from node to root,
 *  keep track of depth of sub node where node travels
 *  and compare it with the unchanged depths of the 
 *  other subnodes
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODEC 100000

struct node {
    struct node* parent;
    struct node* left;
    struct node* right;
    int depth;
    int left_depth;
    int right_depth;
};
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
struct node* rotatetoroot(struct node* n, struct node* root) {
    while (rotate(n) != root) {}
    return root;
}

int max(int n1, int n2) {
    if (n1 < n2) {
        return n2;
    } else {
        return n1;
    }
}

int depth(struct node* n) {
    n->left_depth = n->left ? depth(n->left) : 0;
    n->right_depth = n->right ? depth(n->right) : 0;
    n->depth = 1 + max(n->left_depth, n->right_depth);

    return n->depth;
}

struct node* find_root(struct node* n) {
    while (n->parent) {
        n = n->parent;
    }

    return n;
}

int depth_after_rotate(struct node* n) {
    int depth = n->depth;
    while (n->parent) {
        if (n == n->parent->left) {
            depth = 1 + max(depth-1, n->parent->right_depth+1);
        } else {
            depth = 1 + max(n->parent->left_depth+1, depth-1);
        } 
        n = n->parent;
    }

    return depth;
}

int main() {
    int nodec;
    struct node nodes[MAX_NODEC];
    struct node* root = NULL;
    while (scanf("%d", &nodec) == 1) {
        if (!nodec) break;
        for (int n = 0; n < nodec; n++) {
            int left, right;
            scanf("%d %d", &left, &right);
            left--; right--;
            if (left >= 0) {
                nodes[left].parent = nodes+n;
                nodes[n].left = nodes+left;
            } else {
                nodes[n].left = NULL;
            }
            if (right >= 0) {
                nodes[right].parent = nodes+n;
                nodes[n].right = nodes+right;
            } else {
                nodes[n].right = NULL;
            }
        }
        
        root = find_root(nodes);
        depth(root);

        for (int n = 0; n < nodec; n++) {
            printf("%d\n", depth_after_rotate(nodes+n));
        }
    }

    return EXIT_SUCCESS;
}
