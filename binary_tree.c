
#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

#define nullptr (void(*))0

struct binary_tree *init_binary_tree_heap()
{
    struct binary_tree(*binary_tree_ptr) = (struct binary_tree(*))malloc(sizeof(struct binary_tree));
    binary_tree_ptr->size = 0;
    binary_tree_ptr->root_node_ptr = nullptr;

    // member function ptrs
    binary_tree_ptr->push_item = push_item;
    binary_tree_ptr->remove_item = remove_item;
    binary_tree_ptr->find = find;
    return binary_tree_ptr;
}

struct binary_tree *init_binary_tree_stack(struct binary_tree(*binary_tree_ptr))
{
    binary_tree_ptr->size = 0;
    binary_tree_ptr->root_node_ptr = nullptr;
    return binary_tree_ptr;
}

int push_item(struct binary_tree(*binary_tree_ptr), int data)
{
    struct node(*node_ptr);
    if (binary_tree_ptr->root_node_ptr == nullptr) // first item?
    {
        node_ptr = (struct node(*))malloc(sizeof(struct node));
        node_ptr->smaller_node_ptr = nullptr;
        node_ptr->greater_node_ptr = nullptr;
        node_ptr->status = 2;
        binary_tree_ptr->root_node_ptr = node_ptr;
    }
    else
    { // nope
        node_ptr = (struct node(*))malloc(sizeof(struct node));

        struct node(*kamikaze_node_ptr) = binary_tree_ptr->root_node_ptr; // used to iterate to end of node leaf, nothing else
        struct node(*node_parent_ptr) = kamikaze_node_ptr;
        while (kamikaze_node_ptr != nullptr)
        {
            if (kamikaze_node_ptr->data < data)
            {
                node_parent_ptr = kamikaze_node_ptr;                     // hold prev node for detect last node
                kamikaze_node_ptr = kamikaze_node_ptr->greater_node_ptr; // iter to greater node
                continue;
            }
            if (kamikaze_node_ptr->data > data)
            {
                node_parent_ptr = kamikaze_node_ptr;                     // hold prev node for detect last node
                kamikaze_node_ptr = kamikaze_node_ptr->smaller_node_ptr; // iter to smaller node
                continue;
            }
        }
        if (node_parent_ptr->data < data)
        {
            node_parent_ptr->greater_node_ptr = node_ptr;
            node_ptr->status = 3;
        }
        else
        {
            node_parent_ptr->smaller_node_ptr = node_ptr;
            node_ptr->status = 1;
        }
    }
    node_ptr->data = data;
    binary_tree_ptr->size++;
    return binary_tree_ptr->size;
}

static struct node(*m_target_node_ptr);

int remove_item(struct binary_tree(*binary_tree_ptr), int data)
{
    if (binary_tree_ptr->root_node_ptr == nullptr)
        return 0;

    m_target_node_ptr = binary_tree_ptr->root_node_ptr;
    struct node(*parent_node_ptr) = get_target_node(m_target_node_ptr, data);

    if (parent_node_ptr == nullptr)
        return 0;

    struct node(*g_target_node_ptr) = m_target_node_ptr->greater_node_ptr;
    struct node(*s_target_node_ptr) = m_target_node_ptr->smaller_node_ptr;

    char status = m_target_node_ptr->status;

    free(m_target_node_ptr);

    if (status == 1)
    {
        parent_node_ptr->smaller_node_ptr = g_target_node_ptr;
        if (g_target_node_ptr != nullptr)
        {
            g_target_node_ptr->status = 1;
            merge_node(g_target_node_ptr, s_target_node_ptr);
        }
        return 1;
    }
    if (status == 3)
    {
        parent_node_ptr->greater_node_ptr = g_target_node_ptr;
        if (g_target_node_ptr != nullptr)
        {
            g_target_node_ptr->status = 3;
            merge_node(g_target_node_ptr, s_target_node_ptr);
        }
        return 1;
    }

    return 1;
}

static void merge_node(struct node(*node_kamikaze_ptr), struct node(*s_target_node_ptr))
{
    struct node(*node_safe_ptr) = node_kamikaze_ptr;
    while (node_kamikaze_ptr != nullptr)
    {
        node_safe_ptr = node_kamikaze_ptr;
        node_kamikaze_ptr = node_kamikaze_ptr->smaller_node_ptr;
    }
    node_safe_ptr->smaller_node_ptr = s_target_node_ptr;
}

static struct node *get_target_node(struct node(*target_node_ptr), int data)
{
    struct node(*target_parent_ptr) = target_node_ptr;
    while (target_node_ptr != nullptr)
    {
        if (target_node_ptr->data == data)
            break;

        if (target_node_ptr->data < data)
        {
            target_parent_ptr = target_node_ptr;
            target_node_ptr = target_node_ptr->greater_node_ptr;
            continue;
        }
        if (target_node_ptr->data > data)
        {
            target_parent_ptr = target_node_ptr;
            target_node_ptr = target_node_ptr->smaller_node_ptr;
            continue;
        }
    }

    m_target_node_ptr = target_node_ptr;

    if (target_node_ptr == nullptr)
        return nullptr;

    return target_parent_ptr;
}

int find(struct binary_tree(*binary_tree_ptr), int data)
{
    if (binary_tree_ptr->root_node_ptr == nullptr)
        return 0;

    struct node(*target_node_ptr) = binary_tree_ptr->root_node_ptr;
    while (target_node_ptr != nullptr)
    {
        if (target_node_ptr->data == data)
            break;

        if (target_node_ptr->data < data)
        {
            target_node_ptr = target_node_ptr->greater_node_ptr;
            continue;
        }
        if (target_node_ptr->data > data)
        {
            target_node_ptr = target_node_ptr->smaller_node_ptr;
            continue;
        }
    }

    if (target_node_ptr == nullptr)
        return 0;

    return 1;
}

void print_list(struct node(*target_node_ptr))
{
    struct node(*node_parent_ptr);
    while (target_node_ptr != nullptr)
    {
        printf("Data : %d \n", target_node_ptr->data);

        node_parent_ptr = target_node_ptr;
        target_node_ptr = target_node_ptr->smaller_node_ptr;
        if (target_node_ptr != nullptr)
            print_list(target_node_ptr);

        target_node_ptr = node_parent_ptr->greater_node_ptr;
        if (target_node_ptr != nullptr)
            print_list(target_node_ptr);

        printf("*******************\n");
    }
}
