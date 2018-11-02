#include <iostream>
#include <vector>

using namespace std;

struct node* create_node();
void init_node(struct node* n, struct node* parent);
struct node* add_node(struct node* n);
struct node* create_tree(string exploration);
vector<string> read_input();

const int SUBNODES_NODE_START_BUFFER = 20;

struct node {
    struct node* subtrees;
    struct node* parent;
    int subtreec;
    int subtree_buffer;
    bool toggle;
};

struct node* create_node() {
    struct node* n = (struct node*) malloc(sizeof(struct node));
    init_node(n, NULL);
    return n;
}

void init_node(struct node* n, struct node* parent) {
    n->subtree_buffer = SUBNODES_NODE_START_BUFFER;
    n->subtrees = (struct node*) malloc(sizeof(struct node)*n->subtree_buffer);
    n->parent = parent;
}

struct node* add_node(struct node* n) {
    if (n->subtreec == n->subtree_buffer) {
        n->subtree_buffer *= 2;
        n->subtrees = (struct node*) realloc(n->subtrees, sizeof(n)*n->subtree_buffer);
    }
    struct node* new_node = &n->subtrees[n->subtreec++];
    init_node(new_node, n);
    return new_node;
}

int main() {
    vector<string> scenarios = read_input();
    create_tree(scenarios.back());
    return 0;
}

struct node* create_tree(string exploration) {
     struct node* root = create_node();
     struct node* current = root;

     for (auto instr : exploration) {
         if (instr == '0') {
             current = add_node(current);
         } else {
             current = current->parent;
         }
     }
     return root;
}

vector<string> read_input() {
    vector<string> strings;
    int scenarios; 
    cin >> scenarios;
    
    for (int i = 0; i < scenarios*2; i++) {
        string line;
        cin >> line;
        strings.push_back(line);
    }
    
    return strings;
}
