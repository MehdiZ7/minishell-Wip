/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:47:23 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/28 13:21:53 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parsing.h"

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
		|| tok_type == PIPE)
		return (1);
	return (0);
}

static void	del_noop(void *p)
{
	(void)p;
}

void	cleanup_ast_on_error(t_list **pile, t_list **postfix)
{
	t_node	*root;

	root = NULL;
	if (pile && *pile)
		root = (t_node *)(*pile)->content;
	if (pile)
		ft_lstclear(pile, del_noop);
	if (postfix)
		ft_lstclear(postfix, (void (*)(void *))free_ast_node);
	if (root)
		free_ast_node(root);
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
	if (create_ast_loop(&pile, &postfix, &cur) == NULL)
		return (NULL);
	if (pile == NULL || pile->next != NULL)
	{
		ft_putstr_fd("minishell: invalid expression \n", STDERR_FILENO);
		return (cleanup_ast_on_error(&pile, &postfix_head), NULL);
	}
	cur = (t_node *)pile->content;
	ft_lstclear(&pile, NULL);
	free(pile);
	return (cur);
}
