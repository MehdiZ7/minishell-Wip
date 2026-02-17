/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_infix_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:01:42 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/15 16:40:02 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_type	ft_tok_to_node_type(t_token_type tok_type)
{
	if (tok_type == CMD_OR_ARG)
		return (NODE_CMD);
	if (tok_type == AND)
		return (NODE_AND);
	if (tok_type == OR)
		return (NODE_OR);
	if (tok_type == PIPE)
		return (NODE_PIPE);
	if (tok_type == PAREN_OPEN)
		return (NODE_PAREN_OPEN);
	return (NODE_NULL);
}

void	infix_cleanup_all(t_list **ret, t_list **op_stack)
{
	ft_lstclear(ret, (void (*)(void *))free_ast_node);
	ft_lstclear(op_stack, (void (*)(void *))free_ast_node);
}

t_list	*push_stack(t_list **stack, t_node *node)
{
	t_list	*new;

	new = ft_lstnew(node);
	if (new == NULL)
		return (NULL);
	ft_lstadd_front(stack, new);
	return (*stack);
}

t_list	*ft_lstreverse(t_list *lst)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;

	prev = NULL;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return (prev);
}
