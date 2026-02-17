/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_infix_parenclose.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:27:13 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/15 16:40:32 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		infix_cleanup_all(t_list **ret, t_list **op_stack);

static void	*null_handler(t_infix_to_postfix *p_i)
{
	if ((*p_i).op_stack == NULL)
	{
		ft_putstr_fd("minishell: ast failed: unbalanced paren\n", STDERR_FILENO);
		return (infix_cleanup_all(&(*p_i).ret, &(*p_i).op_stack), NULL);
	}
	return ((void *)0x1);
}

void	*infix_paren_close(t_infix_to_postfix *p_i)
{
	if (null_handler(p_i) == NULL)
		return (NULL);
	while ((*p_i).op_stack != NULL)
	{
		(*p_i).cur_node = (t_node *)(*p_i).op_stack->content;
		if ((*p_i).cur_node->node_type == NODE_PAREN_OPEN)
			break ;
		(*p_i).next_op = (*p_i).op_stack->next;
		ft_lstadd_front(&(*p_i).ret, (*p_i).op_stack);
		(*p_i).op_stack = (*p_i).next_op;
	}
	if ((*p_i).op_stack == NULL
		|| ((t_node *)(*p_i).op_stack->content)->node_type != NODE_PAREN_OPEN)
	{
		ft_putstr_fd("minishell:ast failed: unbalanced paren\n", STDERR_FILENO);
		return (infix_cleanup_all(&(*p_i).ret, &(*p_i).op_stack), NULL);
	}
	else
	{
		(*p_i).next_op = (*p_i).op_stack->next;
		(*p_i).op_stack = (*p_i).next_op;
	}
	(*p_i).tok = (*p_i).tok->next;
	return ((void *)0x1);
}
