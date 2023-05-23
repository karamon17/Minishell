/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:43:08 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/23 16:23:30 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

#include "../minishell.h"

// Function to create a new AST node
t_tree* createNode(void *data, t_tree *left, t_tree *right) {
    t_tree *node = (t_tree*)malloc(sizeof(t_tree));
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

// Function to build the AST recursively
t_tree* buildAST(t_token **tokens)
{
    t_tree  *node;
    t_token *current;

    //Check for NULL or empty token
    if (!(*tokens) ||  (*tokens)->data == NULL)
        return NULL;

    // Get the current token
    current = *tokens;
    *tokens = (*tokens)->next;

    // Create an AST node with the current token's data
    node = createNode(current->data, NULL, NULL);

    // Recursively build the left and right subtrees
    node->left = buildAST(tokens);
    node->right = buildAST(tokens);

    return node;
}

// Function to print the AST in an inorder traversal
void printAST(t_tree *root) 
{
    if (root == NULL) 
        return;

    printAST(root->left);
    printf("%s\n", (char*)root->data);
    printAST(root->right);
}

// Function to free the memory allocated for the AST
void freeAST(t_tree *root) {
    if (root == NULL) {
        return;
    }
    freeAST(root->left);
    freeAST(root->right);
    free(root);
}
