/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:27:51 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/08 17:02:10 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_handling(char *input, size_t start, char *grp)
{
	if (ft_first_char_not_ingroup(input, start, " \t\f\v") == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline\'\n",
			STDERR_FILENO);
		return (-1);
	}
	if (ft_strchr(grp, ft_first_char_not_ingroup(input, start, " \t\f\v")))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putchar_fd(ft_first_char_not_ingroup(input, 2, " \t\f\v"),
			STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

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
	if (ft_strncmp(input, "||", 2) == 0)
	{
		if (error_handling(input, 2, "&|") == -1)
			return (-1);
		return (extract_sep(list, "||", OR, 2));
	}
	else if (input[0] == '|')
	{
		if (error_handling(input, 1, "&|") == -1)
			return (-1);
		return (extract_sep(list, "|", PIPE, 1));
	}
	else if (ft_strncmp(input, "<<", 2) == 0)
	{
		if (error_handling(input, 2, "><&|") == -1)
			return (-1);
		return (extract_sep(list, "<<", HEREDOC, 2));
	}
	else if (input[0] == '<')
	{
		if (error_handling(input, 1, "><&|") == -1)
			return (-1);
		return (extract_sep(list, "<", REDIR_IN, 1));
	}
	else if (!ft_strncmp(input, ">>", 2))
	{
		if (error_handling(input, 2, "><&|") == -1)
			return (-1);
		return (extract_sep(list, ">>", APPEND, 2));
	}
	else if (*input == '>')
	{
		if (error_handling(input, 1, "><&|") == -1)
			return (-1);
		return (extract_sep(list, ">", REDIR_OUT, 1));
	}
	else if (!ft_strncmp(input, "&&", 2))
	{
		if (error_handling(input, 2, "<&|") == -1)
			return (-1);
		return (extract_sep(list, "&&", AND, 2));
	}
	return (0);
}
