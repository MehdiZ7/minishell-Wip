/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:45:10 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/28 13:08:22 by lmilando         ###   ########.fr       */
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

t_redir_node	*create_redir_node(t_redir_type type)
{
	t_redir_node	*node;

	node = ft_calloc(1, sizeof(t_redir_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
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
	t_redir_node	*cur;
	t_redir_node	*next;

	if (!node)
		return ;
	cur = node;
	next = NULL;
	while (cur)
	{
		next = cur->next;
		if (cur->filename)
		{
			free(cur->filename);
			cur->filename = NULL;
		}
		free(cur);
		cur = next;
	}
}

void	free_ast_node(t_node *ast)
{
	if (!ast)
		return ;
	if (ast->node_type == NODE_CMD)
	{
		free_args(ast->command.argv);
		free_redir_node(ast->command.redir);
	}
	else if (ast->node_type == NODE_PIPE)
	{
		free_ast_node(ast->bin_op.first);
		free_ast_node(ast->bin_op.second);
	}
	else if (ast->node_type == NODE_AND)
	{
		free_ast_node(ast->bin_op.first);
		free_ast_node(ast->bin_op.second);
	}
	else if (ast->node_type == NODE_OR)
	{
		free_ast_node(ast->bin_op.first);
		free_ast_node(ast->bin_op.second);
	}
	free(ast);
	ast = NULL;
}
