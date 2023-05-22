/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:43:08 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/20 14:43:10 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

#include <stdio.h>
#include <stdlib.h>

// Structure for tokens obtained from lexical analysis
// typedef struct s_token 
// {
//     char *data;
//     struct s_token *next;
// } t_token;

// Structure for the Abstract Syntax Tree (AST) node
// typedef struct s_tree 
// {
//     void *data;
//     struct s_tree *left;
//     struct s_tree *right;
// } t_tree;

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
