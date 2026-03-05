/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_create_ast_loop.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:09:44 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 13:34:39 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parsing.h"

static void	*handle_operation(t_list **p_pile, t_node **p_cur,
		t_list **p_node_lst)
{
	if (*p_pile == NULL || (*p_pile)->next == NULL)
	{
		ft_putstr_fd("minishell: invalid expression \n", STDERR_FILENO);
		return (cleanup_ast_on_error(p_pile, p_node_lst), NULL);
	}
	(*p_cur)->bin_op.second = pop_stack(p_pile);
	(*p_cur)->bin_op.first = pop_stack(p_pile);
	if (push_stack(p_pile, *p_cur) == NULL)
		return (cleanup_ast_on_error(p_pile, p_node_lst), NULL);
	return ((void *)0x1);
}

void	*create_ast_loop(t_list **p_pile, t_list **p_postfix, t_node **p_cur)
{
	t_list	*next;
	t_list	*node_lst;

	while (*p_postfix != NULL)
	{
		next = (*p_postfix)->next;
		node_lst = *p_postfix;
		*p_cur = (t_node *)node_lst->content;
		if ((*p_cur)->node_type == NODE_CMD)
		{
			if (push_stack(p_pile, *p_cur) == NULL)
				return (cleanup_ast_on_error(p_pile, &node_lst), NULL);
		}
		else if ((*p_cur)->node_type == NODE_AND
			|| (*p_cur)->node_type == NODE_OR
			|| (*p_cur)->node_type == NODE_PIPE)
		{
			if (handle_operation(p_pile, p_cur, &node_lst) == NULL)
				return (NULL);
		}
		free(node_lst);
		*p_postfix = next;
	}
	return ((void *)0x1);
}
