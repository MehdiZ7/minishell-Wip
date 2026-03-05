/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:01:10 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/28 15:16:52 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_token_type(char *value)
{
	if (ft_strncmp(value, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(value, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(value, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(value, "(", 1) == 0)
		return (PAREN_OPEN);
	if (ft_strncmp(value, ")", 1) == 0)
		return (PAREN_CLOSE);
	if (ft_strncmp(value, "<<", 2) == 0)
		return (HEREDOC);
	if (value[0] == '<')
		return (REDIR_IN);
	if (ft_strncmp(value, ">>", 2) == 0)
		return (APPEND);
	if (value[0] == '>')
		return (REDIR_OUT);
	if (ft_strchr(value, '*') != NULL)
		return (WILDCARD);
	return (CMD_OR_ARG);
}

static void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

static t_token	*append_token_helper(t_token **head, t_token **tail,
		char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = create_token(value, type);
	if (new_token == NULL)
		return (free_token_list(*head), NULL);
	if (*head == NULL)
	{
		*head = new_token;
		*tail = new_token;
	}
	else
	{
		(*tail)->next = new_token;
		*tail = new_token;
	}
	return (new_token);
}

static t_token	*append_token(t_token **head, t_token **tail, char *value,
		int is_op)
{
	t_token_type	type;
	size_t			i;

	type = CMD_OR_ARG;
	i = 0;
	if (is_op)
	{
		type = get_token_type(value);
		if (type == APPEND || type == HEREDOC)
			i += 2;
		else if (type == REDIR_IN || type == REDIR_OUT)
			i++;
		if (type == APPEND || type == HEREDOC || type == REDIR_IN
			|| type == REDIR_OUT)
		{
			while (value[i] == ' ')
				i++;
		}
	}
	return (append_token_helper(head, tail, &value[i], type));
}

t_token	*lexer(char *input, t_env *env, int exit_status)
{
	t_tab_str	*temp_tokens;
	t_token		*head;
	t_token		*tail;
	size_t		i;
	t_tab_str	*tokens;

	temp_tokens = ft_split_like_shell(input);
	if (temp_tokens == NULL)
		return (NULL);
	head = NULL;
	tail = NULL;
	i = 0;
	tokens = ft_complete_string_treatment(env, temp_tokens, exit_status);
	ft_free_tab_str(&temp_tokens);
	while (i < tokens->len)
	{
		if (append_token(&head, &tail, tokens->strs[i],
				tokens->is_op[i]) == NULL)
			return (ft_free_tab_str(&tokens), NULL);
		i++;
	}
	ft_free_tab_str(&tokens);
	return (head);
}
