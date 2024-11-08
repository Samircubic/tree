#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include "main.h"

//----------------------------------------------------------------------------------------

int main (int argc, const char *argv[])
{
    tree_t* tree = ctor_tree ();

    push_elem (tree, 10);
    push_elem (tree, 2);
    push_elem (tree, 7);
    push_elem (tree, 90);
    push_elem (tree, 91);
    push_elem (tree, 5);
    push_elem (tree, 89);

    print (tree->node);

    dump_tree (tree);

    dtor_tree (tree);

    return 0;
}

//----------------------------------------------------------------------------------------

check_t push_elem (tree_t* tree, ARG_TREE value) //TODO assert
{
    node_t** node = &tree->node;

    while (*node != 0)
    {
        if (value < (*node)->data) node = &(*node)->left;
        else node = &(*node)->right;
    }

    *node = new_elem (value);

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
    node_t* node = (node_t*) calloc (1, sizeof (node_t)); //TODO

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

void print (node_t* node)
{
    if (node == 0) return;

    printf ("("
            "%d", node->data);

    if (node->left != 0) print (node->left);

    if (node->right != 0) print (node->right);

    printf (")");
}

//----------------------------------------------------------------------------------------

check_t dump_tree (tree_t* tree)
{
    int check = check_tree (tree);

    if (check == ERROR) return ERROR;

    char* name_file_log = "log/log.dot";

    FILE* file = open_file (name_file_log, "w");

    print_log_settings (file);

    print_log_tree (tree->node, file);

    return OK;
}

//----------------------------------------------------------------------------------------

void print_log_settings (FILE* file)
{
    fprintf (file, "\n");
}

//----------------------------------------------------------------------------------------

void print_log_tree (node_t* node, FILE* file)
{
    fprintf (file, "\n");

    if (node->left != 0) print_log_tree (node->left, file);

    if (node->right != 0) print_log_tree (node->right, file);
}

//----------------------------------------------------------------------------------------

FILE* open_file (char* name_file, char* reg)
{
    FILE* file = fopen (name_file, reg);
    assert (file);

    return file;
}

//----------------------------------------------------------------------------------------



