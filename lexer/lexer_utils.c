/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:45:47 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/09 17:31:30 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_first_char_not_ingroup(char *str, size_t start, char *grp)
{
	size_t	i;

	if (str == NULL || grp == NULL || ft_strlen(str) <= start)
		return (0);
	i = start;
	while (str[i] != 0)
	{
		if (ft_strchr(grp, str[i]) == NULL)
			return (str[i]);
		i++;
	}
	return (0);
}

int	ft_isseparator(const char c)
{
	if (c == '|')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '&')
		return (1);
	return (0);
}

int	ft_strlen_without_quotes(char *input, int i)
{
	char	q;
	int		index;

	index = i;
	q = input[i];
	i++;
	while (input[i] && input[i] != q)
		i++;
	if (input[i] == '\0')
		return (-1);
	i++;
	return (i - index);
}

void	free_token(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list;
		if (list->value)
			free(list->value);
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
}
