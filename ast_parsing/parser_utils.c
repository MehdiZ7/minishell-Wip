/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:45:10 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/10 12:15:38 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_ast_node(t_node_type type)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_node));
	new->node_type = type;
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
	if (ast->node_type == NODE_CMD)
	{
		free_args(ast->command.argv);
		free_env(ast->command.env);
		free_redir_node(ast->command.redir);
	}
	else if (ast->node_type == NODE_PIPE)
	{
		free_ast_node(ast->pipe_command.first);
		free_ast_node(ast->pipe_command.second);
	}
	else if (ast->node_type == NODE_AND)
	{
		free_ast_node(ast->and_command.first);
		free_ast_node(ast->and_command.second);
	}
	else if (ast->node_type == NODE_OR)
	{
		free_ast_node(ast->or_command.first);
		free_ast_node(ast->or_command.second);
	}
	free(ast);
	ast = NULL;
}
