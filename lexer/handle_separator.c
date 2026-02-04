/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:27:51 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/03 17:41:19 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extract_sep(t_token **list, char *value, t_token_type type, int len)
{
	t_token	*new;

	new = create_token(value, type);
	if (!new)
		return (-1);
	token_add_back(new, list);
	return (len);
}

int	handle_separator(char *input, t_token **list)
{
	if (!ft_strncmp(input, "||", 2))
		return (extract_sep(list, "||", OR, 2));
	else if (*input == '|')
		return (extract_sep(list, "|", PIPE, 1));
	else if (!ft_strncmp(input, "<<", 2))
		return (extract_sep(list, "<<", HEREDOC, 2));
	else if (*input == '<')
		return (extract_sep(list, "<", REDIR_IN, 1));
	else if (!ft_strncmp(input, ">>", 2))
		return (extract_sep(list, ">>", APPEND, 2));
	else if (*input == '>')
		return (extract_sep(list, ">", REDIR_OUT, 1));
	else if (!ft_strncmp(input, "&&", 2))
		return (extract_sep(list, "&&", AND, 2));
	return (0);
}
