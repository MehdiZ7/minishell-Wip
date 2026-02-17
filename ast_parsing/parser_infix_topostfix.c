/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_infix_topostfix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:22:37 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/15 16:41:51 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_parser_step(t_node *node);

t_node_type	ft_tok_to_node_type(t_token_type tok_type);
void		infix_cleanup_all(t_list **ret, t_list **op_stack);
t_list		*push_stack(t_list **stack, t_node *node);
t_list		*ft_lstreverse(t_list *lst);
void		*infix_paren_close(t_infix_to_postfix *p_i);

static void	*infix_cmdorarg(t_infix_to_postfix *p_i, t_minishell *minishell)
{
	(*p_i).new_cmd = NULL;
	(*p_i).tok = create_ast_command(&(*p_i).new_cmd, (*p_i).tok,
			minishell->env);
	if ((*p_i).new_cmd == NULL)
		return (infix_cleanup_all(&(*p_i).ret, &(*p_i).op_stack), NULL);
	if (push_stack(&(*p_i).ret, (*p_i).new_cmd) == NULL)
		return (free_ast_node((*p_i).new_cmd), infix_cleanup_all(&(*p_i).ret,
				&(*p_i).op_stack), NULL);
	return ((void *)0x1);
}

static void	*infix_paren_open(t_infix_to_postfix *p_i)
{
	(*p_i).cur_node = create_ast_node(ft_tok_to_node_type((*p_i).tok->type));
	if ((*p_i).cur_node == NULL)
		return (infix_cleanup_all(&(*p_i).ret, &(*p_i).op_stack), NULL);
	if (push_stack(&(*p_i).op_stack, (*p_i).cur_node) == NULL)
		return (free_ast_node((*p_i).cur_node), infix_cleanup_all(&(*p_i).ret,
				&(*p_i).op_stack), NULL);
	(*p_i).tok = (*p_i).tok->next;
	return ((void *)0x1);
}

static void	*infix_operand(t_infix_to_postfix *p_i)
{
	while ((*p_i).op_stack != NULL)
	{
		(*p_i).cur_node = (t_node *)(*p_i).op_stack->content;
		if ((*p_i).cur_node == NULL)
			break ;
		if ((*p_i).cur_node->node_type == NODE_PAREN_OPEN)
			break ;
		if (((*p_i).node_type == NODE_AND || (*p_i).node_type == NODE_OR)
			&& ((*p_i).cur_node->node_type == NODE_AND
				|| (*p_i).cur_node->node_type == NODE_OR))
			;
		else if ((*p_i).node_type > (*p_i).cur_node->node_type)
			break ;
		(*p_i).next_op = (*p_i).op_stack->next;
		ft_lstadd_front(&(*p_i).ret, (*p_i).op_stack);
		(*p_i).op_stack = (*p_i).next_op;
	}
	(*p_i).cur_node = create_ast_node((*p_i).node_type);
	if ((*p_i).cur_node == NULL)
		return (infix_cleanup_all(&(*p_i).ret, &(*p_i).op_stack), NULL);
	if (push_stack(&(*p_i).op_stack, (*p_i).cur_node) == NULL)
		return (free_ast_node((*p_i).cur_node), infix_cleanup_all(&(*p_i).ret,
				&(*p_i).op_stack), NULL);
	(*p_i).tok = (*p_i).tok->next;
	return ((void *)0x1);
}

static void	*infix_loop(t_infix_to_postfix *p_i, t_minishell *minishell)
{
	if ((*p_i).tok->type == CMD_OR_ARG || (*p_i).tok->type == ENV)
	{
		if (infix_cmdorarg(p_i, minishell) == NULL)
			return (NULL);
	}
	else if ((*p_i).tok->type == PAREN_OPEN)
	{
		if (infix_paren_open(p_i) == NULL)
			return (NULL);
	}
	else if ((*p_i).tok->type == PAREN_CLOSE)
	{
		if (infix_paren_close(p_i) == NULL)
			return (NULL);
	}
	else if ((*p_i).tok->type == AND || (*p_i).tok->type == OR
		|| (*p_i).tok->type == PIPE)
	{
		(*p_i).node_type = ft_tok_to_node_type((*p_i).tok->type);
		if (infix_operand(p_i) == NULL)
			return (NULL);
	}
	return ((void *)0x1);
}

t_list	*infix_to_postfix(t_minishell *minishell)
{
	t_infix_to_postfix	i;

	i.op_stack = NULL;
	i.ret = NULL;
	i.tok = minishell->tokens;
	i.cur_node = NULL;
	while (i.tok != NULL)
		if (infix_loop(&i, minishell) == NULL)
			return (NULL);
	while (i.op_stack != NULL)
	{
		i.cur_node = (t_node *)i.op_stack->content;
		if (i.cur_node->node_type == NODE_PAREN_OPEN)
			return (ft_putstr_fd("minishell:ast failed: unbalanced paren\n",
					STDERR_FILENO), \
					infix_cleanup_all(&i.ret, &i.op_stack), NULL);
		i.next_op = i.op_stack->next;
		ft_lstadd_front(&i.ret, i.op_stack);
		i.op_stack = i.next_op;
	}
	i.ret = ft_lstreverse(i.ret);
	return (i.ret);
}
