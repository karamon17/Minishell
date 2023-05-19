#include "../minishell.h"

t_tree *createNode(char *data, t_tree *left, t_tree *right) {
    t_tree *node = (t_tree*)malloc(sizeof(t_tree));
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

t_tree *createLeafNode(char *data) 
{
    return createNode(data, NULL, NULL);
}
