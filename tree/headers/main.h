#ifndef MAIN_H
#define MAIN_H

#define ARG_TREE int //TODO typedef

typedef enum check
{
    ERROR, //TODO more errors
    OK
} check_t;

typedef struct node
{
    ARG_TREE data;
    struct node* left;
    struct node* right;
} node_t;

typedef struct tree
{
    node_t* node;
    int size;
} tree_t;

/*

*/
node_t*     new_elem            (ARG_TREE value);

/*

*/
tree_t*     ctor_tree           ();

/*

*/
check_t     dtor_tree           (tree_t* tree);

/*

*/
check_t     check_tree          (tree_t* tree);

/*

*/
check_t     dtor_elem           (node_t* node); //TODO dtor node

/*

*/
check_t     push_elem           (tree_t* tree, ARG_TREE value);

/*

*/
void        print               (node_t* node); //TODO rename

/*

*/
check_t     dump_tree           (tree_t* tree);

/*

*/
FILE*       open_file           (char* name_file, char* reg);

/*

*/
void        print_log_tree      (node_t* node, FILE* file);

/*

*/
void        print_log_settings  (FILE* file);

#endif // MAIN_H
