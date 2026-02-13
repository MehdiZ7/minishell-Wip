/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_infix_topostfix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:22:37 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/13 13:25:33 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_parser_step(t_node *node);
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

void	cleanup_all(t_list **ret, t_list **op_stack)
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

t_list *ft_lstreverse(t_list *lst)
{
	t_list *prev;
	t_list *current;
	t_list *next;

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

t_list	*infix_to_postfix(t_minishell *minishell)
{
	t_list		*op_stack;
	t_list		*ret;
	t_token		*tok;
	t_node		*cur_node;
	t_list		*next_op;
	t_node_type	node_type;
	t_node		*new_cmd;

	op_stack = NULL;
	ret = NULL;
	tok = minishell->tokens;
	cur_node = NULL;
	while (tok != NULL)
	{
		if (tok->type == CMD_OR_ARG)
		{
			new_cmd = NULL;
			tok = create_ast_command(&new_cmd, tok, minishell->env);
			if (new_cmd == NULL)
				return (cleanup_all(&ret, &op_stack), NULL);
			if (push_stack(&ret, new_cmd) == NULL)
				return (free_ast_node(new_cmd), cleanup_all(&ret, &op_stack),
					NULL);
		}
		else if (tok->type == PAREN_OPEN)
		{
			cur_node = create_ast_node(ft_tok_to_node_type(tok->type));
			if (cur_node == NULL)
				return (cleanup_all(&ret, &op_stack), NULL);
			if (push_stack(&op_stack, cur_node) == NULL)
				return (free_ast_node(cur_node), cleanup_all(&ret, &op_stack),
					NULL);
			tok = tok->next;
		}
		else if (tok->type == PAREN_CLOSE)
		{
			if (op_stack == NULL)
			{
				ft_putstr_fd("minishell: ast parsing failed: \
					unbalanced parenthesis\n",
								STDERR_FILENO);
				return (cleanup_all(&ret, &op_stack), NULL);
			}
			while (op_stack != NULL)
			{
				cur_node = (t_node *)op_stack->content;
				if (cur_node->node_type == NODE_PAREN_OPEN)
					break ;
				next_op = op_stack->next;
				ft_lstadd_front(&ret, op_stack);
				op_stack = next_op;
			}
			if (op_stack == NULL
				|| ((t_node *)op_stack->content)->node_type != NODE_PAREN_OPEN)
			{
				ft_putstr_fd("minishell: ast parsing failed: \
					unbalanced parenthesis\n",
								STDERR_FILENO);
				return (cleanup_all(&ret, &op_stack), NULL);
			}
			else
			{
				next_op = op_stack->next;
				op_stack = next_op;
			}
			tok = tok->next;
		}
		else if (tok->type == AND || tok->type == OR || tok->type == PIPE)
		{
			node_type = ft_tok_to_node_type(tok->type);
			while (op_stack != NULL)
			{
				cur_node = (t_node *)op_stack->content;
				if (cur_node == NULL)
					break ;
				if (cur_node->node_type == NODE_PAREN_OPEN)
					break ;
				if (node_type > cur_node->node_type)
					break ;
				next_op = op_stack->next;
				ft_lstadd_front(&ret, op_stack);
				op_stack = next_op;
			}
			cur_node = create_ast_node(node_type);
			if (cur_node == NULL)
				return (cleanup_all(&ret, &op_stack), NULL);
			if (push_stack(&op_stack, cur_node) == NULL)
				return (free_ast_node(cur_node), cleanup_all(&ret, &op_stack),
					NULL);
			tok = tok->next;
		}
	}
	while (op_stack != NULL)
	{
		cur_node = (t_node *)op_stack->content;
		if (cur_node->node_type == NODE_PAREN_OPEN)
		{
			ft_putstr_fd("minishell: ast parsing failed: \
					unbalanced parenthesis\n",
							STDERR_FILENO);
			return (cleanup_all(&ret, &op_stack), NULL);
		}
		next_op = op_stack->next;
		ft_lstadd_front(&ret, op_stack);
		op_stack = next_op;
	}
	ret = ft_lstreverse(ret);
	return (ret);
}
