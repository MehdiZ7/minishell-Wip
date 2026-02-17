/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:47:23 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/15 15:27:27 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_lstadd_back_redir(t_redir_node **list, t_redir_node *elt);
int			cmd_node_is_arg(t_token *cur_tok, t_node *cmd_node, int *p_j);
void		*cmd_node_is_redir(t_redir_node **p_redir, t_token *cur_tok,
				t_node *cmd_node);
void		*create_ast_command_loop(t_token **p_cur_tok,
				t_redir_node **p_redir, t_node *cmd_node);
t_token		*create_ast_command(t_node **result, t_token *tok, t_env *envp);

int	ft_tok_is_op(t_token_type tok_type)
{
	if (tok_type == AND || tok_type == OR || tok_type == PAREN_CLOSE
		|| tok_type == PAREN_CLOSE || tok_type == PIPE)
		return (1);
	return (0);
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

void	*create_ast_loop(t_list **p_pile, t_list **p_postfix_head,
		t_list **p_postfix, t_node **p_cur)
{
	while (*p_postfix != NULL)
	{
		*p_cur = (t_node *)(*p_postfix)->content;
		if ((*p_cur)->node_type == NODE_CMD)
		{
			if (push_stack(p_pile, *p_cur) == NULL)
				return (cleanup_ast_on_error(p_pile, p_postfix_head), NULL);
		}
		else if ((*p_cur)->node_type == NODE_AND || \
		(*p_cur)->node_type == NODE_OR || (*p_cur)->node_type == NODE_PIPE)
		{
			if (*p_pile == NULL || (*p_pile)->next == NULL)
			{
				ft_putstr_fd("minishell: invalid expression 1\n",
					STDERR_FILENO);
				return (cleanup_ast_on_error(p_pile, p_postfix_head), NULL);
			}
			(*p_cur)->bin_op.second = pop_stack(p_pile);
			(*p_cur)->bin_op.first = pop_stack(p_pile);
			if (push_stack(p_pile, *p_cur) == NULL)
				return (cleanup_ast_on_error(p_pile, p_postfix_head), NULL);
		}
		*p_postfix = (*p_postfix)->next;
	}
	return ((void *)0x1);
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
	if (create_ast_loop(&pile, &postfix_head, &postfix, &cur) == NULL)
		return (NULL);
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
