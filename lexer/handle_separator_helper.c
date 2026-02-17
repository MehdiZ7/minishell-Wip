/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_separator_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:43:19 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/15 14:09:20 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int		error_handling(char *input, size_t start, char *grp);
int		extract_sep(t_token **list, char *value, t_token_type type, int len);
char	*ft_extract_str(char *input, int *p_len);

int	handle_separator_vertical_bar(char *input, t_token **list)
{
	char	*str;
	int		len;

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
		str = ft_extract_str(&input[2], &len);
		if (str == NULL)
			return (-1);
		return (extract_sep(list, str, HEREDOC, 2) + len);
	}
	return (INT_MAX);
}

int	handle_separator_comp_sign(char *input, t_token **list)
{
	char	*str;
	int		len;

	if (input[0] == '<')
	{
		if (error_handling(input, 1, "><&|") == -1)
			return (-1);
		str = ft_extract_str(&input[1], &len);
		if (str == NULL)
			return (-1);
		return (extract_sep(list, str, REDIR_IN, 1) + len);
	}
	else if (!ft_strncmp(input, ">>", 2))
	{
		if (error_handling(input, 2, "><&|") == -1)
			return (-1);
		str = ft_extract_str(&input[2], &len);
		if (str == NULL)
			return (-1);
		return (extract_sep(list, str, APPEND, 2) + len);
	}
	return (INT_MAX);
}

int	handle_separator_comp_sign2(char *input, t_token **list)
{
	char	*str;
	int		len;

	if (*input == '>')
	{
		if (error_handling(input, 1, "><&|") == -1)
			return (-1);
		str = ft_extract_str(&input[1], &len);
		if (str == NULL)
			return (-1);
		return (extract_sep(list, str, REDIR_OUT, 1) + len);
	}
	else if (!ft_strncmp(input, "&&", 2))
	{
		if (error_handling(input, 2, "<&|") == -1)
			return (-1);
		return (extract_sep(list, "&&", AND, 2));
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `&'\n",
			STDERR_FILENO);
		return (-1);
	}
	return (INT_MAX);
}
