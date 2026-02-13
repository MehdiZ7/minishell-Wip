/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:47:23 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/12 10:10:57 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lstadd_back_redir(t_redir_node **list, t_redir_node *elt)
{
	t_redir_node	*cur;

	if (*list == NULL)
		return ;
	cur = *list;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = elt;
}

static int	ft_tok_is_op(t_token_type tok_type)
{
	if (tok_type == AND || tok_type == OR || tok_type == PAREN_CLOSE
		|| tok_type == PAREN_CLOSE || tok_type == PIPE)
		return (1);
	return (0);
}

t_token	*create_ast_command(t_node **result, t_token *tok, t_env *envp)
{
	t_node			*cmd_node;
	t_token			*cur_tok;
	size_t			len;
	size_t			j;
	t_redir_node	*redir;

	cmd_node = create_ast_node(NODE_CMD);
	if (cmd_node == NULL)
		return (NULL);
	cur_tok = tok;
	len = 0;
	while (cur_tok != NULL && ft_tok_is_op(cur_tok->type) == 0)
	{
		if (cur_tok->type == CMD_OR_ARG)
			len++;
		cur_tok = cur_tok->next;
	}
	cmd_node->command.argc = (int)len;
	cmd_node->command.argv = ft_calloc(len + 1, sizeof(char *));
	if (cmd_node->command.argv == NULL)
		return (free_ast_node(cmd_node), NULL);
	cmd_node->command.env = envp;
	cur_tok = tok;
	j = 0;
	while (cur_tok != NULL)
	{
		if (cur_tok->type == CMD_OR_ARG)
		{
			cmd_node->command.argv[j] = ft_strdup(cur_tok->value);
			if (cmd_node->command.argv[j] == NULL)
				return (free_ast_node(cmd_node), NULL);
			j++;
		}
		else if (cur_tok->type == REDIR_IN || cur_tok->type == REDIR_OUT
			|| cur_tok->type == HEREDOC || cur_tok->type == APPEND)
		{
			redir = create_redir_node(REDIR_IN_FILE);
			if (cur_tok->type == REDIR_OUT)
				redir->type = REDIR_OUT_FILE;
			else if (cur_tok->type == HEREDOC)
				redir->type = REDIR_HEREDOC;
			else if (cur_tok->type == APPEND)
				redir->type = REDIR_APPEND;
			if (cmd_node->command.redir == NULL)
				cmd_node->command.redir = redir;
			else
				ft_lstadd_back_redir(&(cmd_node->command.redir), redir);
			redir->filename = ft_strdup(cur_tok->value);
			if (redir->filename == NULL)
				return (free_ast_node(cmd_node), NULL);
		}
		else
			break ;
		cur_tok = cur_tok->next;
	}
	*result = cmd_node;
	return (cur_tok);
}

static void	cleanup_ast_on_error(t_list **pile, t_list **postfix)
{
	ft_lstclear(pile, (void (*)(void *))free_ast_node);
	ft_lstclear(postfix, (void (*)(void *))free_ast_node);
}

t_node	*pop_stack(t_list **stack)
{
	t_list	*tmp;
	t_node	*node;

	if (*stack == NULL)
		return (NULL);
	node = (t_node *)((*stack)->content);
	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	return (node);
}

t_node	*create_ast(t_minishell *minishell)
{
	t_list	*postfix;
	t_list	*postfix_head;
	t_list	*pile;
	t_node	*cur;

	postfix = infix_to_postfix(minishell);
	if (postfix == NULL)
		return (NULL);
	postfix_head = postfix;
	pile = NULL;
	while (postfix != NULL)
	{
		cur = (t_node *)postfix->content;
		if (cur->node_type == NODE_CMD)
		{
			if (push_stack(&pile, cur) == NULL)
				return (cleanup_ast_on_error(&pile, &postfix_head), NULL);
		}
		else if (cur->node_type == NODE_AND || cur->node_type == NODE_OR
			|| cur->node_type == NODE_PIPE)
		{
			if (pile == NULL || pile->next == NULL)
			{
				ft_putstr_fd("minishell: invalid expression 1\n",
					STDERR_FILENO);
				return (cleanup_ast_on_error(&pile, &postfix_head), NULL);
			}
			cur->bin_op.second = pop_stack(&pile);
			cur->bin_op.first = pop_stack(&pile);
			if (push_stack(&pile, cur) == NULL)
				return (cleanup_ast_on_error(&pile, &postfix_head), NULL);
		}
		postfix = postfix->next;
	}
	if (pile == NULL || pile->next != NULL)
	{
		ft_putstr_fd("minishell: invalid expression 2\n", STDERR_FILENO);
		return (cleanup_ast_on_error(&pile, &postfix_head), NULL);
	}
	cur = (t_node *)pile->content;
	ft_lstclear(&pile, NULL);
	ft_lstclear(&postfix_head, NULL);
	return (cur);
}
