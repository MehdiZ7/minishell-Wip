/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:45:47 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/05 16:17:36 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isoperator(const char c)
{
	if (c == '|')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	return (0);
}

int	skip_quotes(char *input, int i)
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
