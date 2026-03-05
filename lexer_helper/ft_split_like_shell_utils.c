/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_like_shell_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:10:13 by lmilando          #+#    #+#             */
/*   Updated: 2026/03/01 14:47:04 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

void	*append_helper(t_tab_str **p_tab, char *str, size_t start, size_t len)
{
	char	*temp;

	temp = ft_substr(str, start, len);
	if (temp == NULL)
		return (ft_free_tab_str(p_tab), NULL);
	if (ft_append_str_to_tab_str(p_tab, temp) == 0)
		return (ft_free_tab_str(p_tab), free(temp), NULL);
	free(temp);
	return ((void *)0x1);
}

int	is_split_operator(char c)
{
	return (ft_strchr("|&()<>", c) != NULL);
}

int	is_redir_or_heredoc(char *str, size_t i)
{
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (2);
		return (1);
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (2);
		return (1);
	}
	return (0);
}

static int	get_redir_or_heredoc_end(char *str, size_t start, int redir_len)
{
	size_t	i;
	char	quote;

	quote = 0;
	i = start + redir_len;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '"' || str[i] == '\'')
		quote = str[i++];
	while (str[i])
	{
		if (quote == 0 && (is_split_operator(str[i]) || str[i] == ' '))
			break ;
		if (quote != 0 && str[i] == quote)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

size_t	get_operator_end(char *str, size_t start)
{
	int		redir_len;

	redir_len = is_redir_or_heredoc(str, start);
	if (redir_len > 0)
		return (get_redir_or_heredoc_end(str, start, redir_len));
	if (ft_strncmp(&str[start], "&&", 2) == 0 || ft_strncmp(&str[start], "||",
			2) == 0)
		return (start + 2);
	if (ft_strchr("|()", str[start]) != NULL)
		return (start + 1);
	return (start);
}
