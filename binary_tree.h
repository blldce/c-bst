#ifndef BINARY_H
#define BINARY_H 1

struct binary_tree
{
    struct node(*root_node_ptr);                    // 8 bytes
    int size;                                       // 4 bytes
    int (*push_item)(struct binary_tree(*), int);   // 8 bytes
    int (*remove_item)(struct binary_tree(*), int); // 8 bytes
    int (*find)(struct binary_tree(*), int);        // 8 bytes
};

struct node
{
    int data;                       // 4 bytes
    char status : 3;                // 1 byte (3 bit fields)
    struct node(*smaller_node_ptr); // 8 bytes
    struct node(*greater_node_ptr); // 8 bytes
};

extern struct binary_tree *
init_binary_tree_heap();

extern struct binary_tree *init_binary_tree_stack(struct binary_tree(*));

// member functions
extern int push_item(struct binary_tree(*), int);
extern int remove_item(struct binary_tree(*), int);
extern int find(struct binary_tree(*), int);

// internals
static struct node *get_target_node(struct node(*), int);
static void merge_node(struct node(*), struct node(*));
static void print_list(struct node(*));

#endif