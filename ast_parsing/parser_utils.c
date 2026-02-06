/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:45:10 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/06 14:06:19 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_ast_node(t_node_type type)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = type;
	new->args = NULL;
	new->left = NULL;
	new->right = NULL;
	new->redir = NULL;
	return (new);
}

void	free_args(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	argv = NULL;
}

void	free_redir_node(t_redir_node *node)
{
	t_redir_node	*tmp;

	if (!node)
		return ;
	while (node)
	{
		tmp = node->next;
		if (node->filename)
		{
			free(node->filename);
			node->filename = NULL;
		}
		if (node->next)
		{
			free(node->next);
			node->next = NULL;
		}
		free(node);
		node = tmp;
	}
	node = NULL;
}

void	free_ast_node(t_node *ast)
{
	if (!ast)
		return ;
	free_ast_node(ast->left);
	free_ast_node(ast->right);
	free_args(ast->args);
	free_redir_node(ast->redir);

}
