#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include "main.h"

//----------------------------------------------------------------------------------------

int main ()
{
    tree_t* tree = ctor_tree ();

    push_elem (tree, 10);
    push_elem (tree, 2);
    push_elem (tree, 7);
    push_elem (tree, 90);
    push_elem (tree, 91);
    push_elem (tree, 5);
    push_elem (tree, 89);
    push_elem (tree, 78);
    push_elem (tree, 97);
    push_elem (tree, 1);

    pop_elem (tree, 89);

    print_tree (tree->node);
    printf ("\n");

    dump_tree (tree);

    dump_tree (tree);

    dtor_tree (tree);

    return 0;
}

//----------------------------------------------------------------------------------------

check_t pop_elem (tree_t* tree, ARG_TREE value)
{
    assert (tree);

    node_t* node_value = walk_tree (tree->node, value);

    if (node_value != 0)
    {
        if (node_value->parent->left == node_value)
        {
            node_value->parent->left = 0;
        }
        else
        {
            node_value->parent->right = 0;
        }

        dtor_elem (node_value);

        return OK;
    }

    return ERROR;
}

//----------------------------------------------------------------------------------------

node_t* walk_tree (node_t* node, ARG_TREE value)
{
    assert (node);

    node_t* node_value = 0;

    if (node->left != 0)
    {
        if (node->left->data == value && node->left->left == 0 && node->left->right == 0)
        {
            return node->left;
        }
        else
        {
            node_value = walk_tree (node->left, value);
        }
    }

    if (node->right != 0)
    {
        if (node->right->data == value && node->right->left == 0 && node->right->right == 0)
        {
            return node->right;
        }
        else
        {
            node_value = walk_tree (node->right, value);
        }
    }

    return node_value;
}

//----------------------------------------------------------------------------------------

check_t push_elem (tree_t* tree, ARG_TREE value)
{
    assert (tree);

    node_t** node = &tree->node;
    node_t** last_node = 0;

    while (*node != 0)
    {
        last_node = node;

        if (value < (*node)->data) node = &(*node)->left;
        else node = &(*node)->right;
    }

    *node = new_elem (value);

    if (last_node != 0)
    {
        (*node)->parent = *last_node;
    }

    return OK;
}

//----------------------------------------------------------------------------------------

tree_t* ctor_tree ()
{
    tree_t* tree = (tree_t*) calloc (1, sizeof (tree_t));
    assert (tree);

    return tree;
}

//----------------------------------------------------------------------------------------

node_t* new_elem (ARG_TREE value)
{
    node_t* node = (node_t*) calloc (1, sizeof (node_t));
    assert (node);

    node->data = value;

    node->left = 0;
    node->right = 0;

    return node;
}

//----------------------------------------------------------------------------------------

check_t dtor_tree (tree_t* tree)
{
    if (check_tree (tree) == ERROR) return ERROR;

    if (tree->node != 0) dtor_elem (tree->node);

    free (tree);

    return OK;
}

//----------------------------------------------------------------------------------------

check_t dtor_elem (node_t* node)
{
    if (node == 0) return ERROR;

    if (node->left != 0) dtor_elem (node->left);

    if (node->right != 0) dtor_elem (node->right);

    free (node);

    return OK;
}

//----------------------------------------------------------------------------------------

check_t check_tree (tree_t* tree)
{
    if (tree->node == 0) return ERROR;
    if (tree->size < 0) return ERROR;

    return OK;
}

//----------------------------------------------------------------------------------------

void print_tree (node_t* node)
{
    if (node == 0) return;

    printf ("("
            "%d", node->data);

    if (node->left != 0) print_tree (node->left);

    if (node->right != 0) print_tree (node->right);

    printf (")");
}

//----------------------------------------------------------------------------------------

check_t dump_tree (tree_t* tree)
{
    int check = check_tree (tree);

    if (check == ERROR) return ERROR;

    FILE* file = open_file (NAME_FILE_LOG, "w");

    fprintf (file,  "digraph G\n"
                    "{\n");

    print_log_settings (file);

    fprintf (file, "{\n");

    print_log_tree (tree->node, file);

    fprintf (file, "}\n");

    fprintf (file, "}\n");

    return OK;
}

//----------------------------------------------------------------------------------------

void print_log_settings (FILE* file)
{
    fprintf (file,  "rankdir=HR\n"
                    "bgcolor = \"#fccccc\"\n"
                    "node[color = \"#800000\", fontsize = 15]\n"
                    "edge[color = \"#800000\", fontsize = 20]\n"
                    "subgraph cluster_tree\n");
}

//----------------------------------------------------------------------------------------

void print_log_tree (node_t* node, FILE* file)
{
    fprintf (file,  "\tnode_%p [color = blue, shape=record, "
                    "label = \"{POINTER: %p | DATA: %d | {L_NODE: %p | R_NODE: %p}}\"];\n",
                    node, node, node->data, node->left, node->right);

    if (node->left != 0)
    {
        fprintf (file, "\tnode_%p -> node_%p;\n", node, node->left);

        print_log_tree (node->left, file);
    }

    if (node->right != 0)
    {
        fprintf (file, "\tnode_%p -> node_%p;\n", node, node->right);

        print_log_tree (node->right, file);
    }
}

//----------------------------------------------------------------------------------------

FILE* open_file (const char* name_file, const char* reg)
{
    FILE* file = fopen (name_file, reg);
    assert (file);

    return file;
}

//----------------------------------------------------------------------------------------

