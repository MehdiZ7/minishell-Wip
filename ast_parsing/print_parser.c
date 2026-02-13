/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:19:32 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/11 22:16:12 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_node_type(t_node_type type)
{
	if (type == NODE_CMD)
		ft_printf("CMD");
	else if (type == NODE_AND)
		ft_printf("AND");
	else if (type == NODE_OR)
		ft_printf("OR");
	else if (type == NODE_PIPE)
		ft_printf("PIPE");
	else if (type == NODE_PAREN_OPEN)
		ft_printf("(");
	else if (type == NODE_NULL)
		ft_printf("NULL");
	else
		ft_printf("UNKNOWN");
}
void	print_postfix_list(t_list *postfix, char *str)
{
	t_list	*cur;
	t_node	*node;
	int		i;
	int		j;

	if (postfix == NULL)
	{
		ft_printf("Liste %s vide\n", str);
		return ;
	}
	ft_printf("====Liste %s Postfix===\n", str);
	cur = postfix;
	i = 0;
	while (cur != NULL)
	{
		node = (t_node *)cur->content;
		ft_printf("[%d] ", i);
		if (node == NULL)
			ft_printf("NODE NULL\n");
		else if (node->node_type == NODE_CMD)
		{
			ft_printf("CMD: ");
			j = 0;
			while (j < node->command.argc)
				ft_printf("%s ", node->command.argv[j++]);
		}
		else
			print_node_type(node->node_type);
		ft_printf("\n");
		cur = cur->next;
		i++;
	}
}

void	print_ast(t_node *node, int depth)
{
	int	i;
	int	j;

	if (node == NULL)
		return ;
	i = 0;
	while (i < depth)
	{
		ft_printf(" ");
		i++;
	}
	if (node->node_type == NODE_CMD)
	{
		ft_printf("CMD: ");
		j = 0;
		while (j < node->command.argc)
		{
			ft_printf("%s ", node->command.argv[j]);
			j++;
		}
		ft_printf("\n");
	}
	else if (node->node_type == NODE_AND)
		ft_printf("AND\n");
	else if (node->node_type == NODE_OR)
		ft_printf("OR\n");
	else if (node->node_type == NODE_PIPE)
		ft_printf("PIPE\n");
	if (node->node_type == NODE_AND || node->node_type == NODE_OR
		|| node->node_type == NODE_PIPE)
	{
		print_ast(node->bin_op.first, depth + 1);
		print_ast(node->bin_op.second, depth + 1);
	}
}
