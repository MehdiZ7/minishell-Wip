/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_create_ast_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 09:29:54 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/15 15:29:46 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tok_is_op(t_token_type tok_type);

void	ft_lstadd_back_redir(t_redir_node **list, t_redir_node *elt)
{
	t_redir_node	*cur;

	if (*list == NULL)
		return ;
	cur = *list;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = elt;
}

int	cmd_node_is_arg(t_token *cur_tok, t_node *cmd_node, size_t *p_j)
{
	cmd_node->command.argv[*p_j] = ft_strdup(cur_tok->value);
	if (cmd_node->command.argv[*p_j] == NULL)
		return (free_ast_node(cmd_node), 0);
	(*p_j)++;
	return (1);
}

void	*cmd_node_is_redir(t_redir_node **p_redir, t_token *cur_tok,
		t_node *cmd_node)
{
	*p_redir = create_redir_node(REDIR_IN_FILE);
	if (cur_tok->type == REDIR_OUT)
		(*p_redir)->type = REDIR_OUT_FILE;
	else if (cur_tok->type == HEREDOC)
		(*p_redir)->type = REDIR_HEREDOC;
	else if (cur_tok->type == APPEND)
		(*p_redir)->type = REDIR_APPEND;
	if (cmd_node->command.redir == NULL)
		cmd_node->command.redir = (*p_redir);
	else
		ft_lstadd_back_redir(&(cmd_node->command.redir), *p_redir);
	(*p_redir)->filename = ft_strdup(cur_tok->value);
	if ((*p_redir)->filename == NULL)
		return (free_ast_node(cmd_node), NULL);
	return (p_redir);
}

void	*create_ast_command_loop(t_token **p_cur_tok, t_redir_node **p_redir,
		t_node *cmd_node)
{
	size_t	j;

	j = 0;
	while (*p_cur_tok != NULL)
	{
		if ((*p_cur_tok)->type == CMD_OR_ARG || (*p_cur_tok)->type == ENV)
		{
			if (cmd_node_is_arg((*p_cur_tok), cmd_node, &j) == 0)
				return (NULL);
		}
		else if ((*p_cur_tok)->type == REDIR_IN
			|| (*p_cur_tok)->type == REDIR_OUT || (*p_cur_tok)->type == HEREDOC
			|| (*p_cur_tok)->type == APPEND)
		{
			if (cmd_node_is_redir(p_redir, (*p_cur_tok), cmd_node) == NULL)
				return (NULL);
		}
		else
			break ;
		*p_cur_tok = (*p_cur_tok)->next;
	}
	return ((void *)0x1);
}

t_token	*create_ast_command(t_node **result, t_token *tok, t_env *envp)
{
	t_node			*cmd_node;
	t_token			*cur_tok;
	size_t			len;
	t_redir_node	*redir;

	cmd_node = create_ast_node(NODE_CMD);
	if (cmd_node == NULL)
		return (NULL);
	cur_tok = tok;
	len = 0;
	while (cur_tok != NULL && ft_tok_is_op(cur_tok->type) == 0)
	{
		if (cur_tok->type == CMD_OR_ARG || cur_tok->type == ENV)
			len++;
		cur_tok = cur_tok->next;
	}
	cmd_node->command.argc = (int)len;
	cmd_node->command.argv = ft_calloc(len + 1, sizeof(char *));
	if (cmd_node->command.argv == NULL)
		return (free_ast_node(cmd_node), NULL);
	cmd_node->command.env = envp;
	if (create_ast_command_loop(&tok, &redir, cmd_node) == NULL)
		return (NULL);
	*result = cmd_node;
	return (tok);
}
