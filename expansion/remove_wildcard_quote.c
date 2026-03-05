/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:47:16 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/28 14:18:33 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_size(char *src)
{
	int		i;
	int		size;
	char	quote;

	i = 0;
	size = 0;
	quote = 0;
	while (src[i])
	{
		if (quote && src[i] == quote)
			quote = 0;
		else if (!quote && (src[i] == '\'' || src[i] == '"'))
			quote = src[i];
		else
			size++;
		i++;
	}
	return (size);
}

static char	*copy_removed(char *dest, char *src)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (quote && src[i] == quote)
			i++;
		else if (!quote && (src[i] == '\'' || src[i] == '"'))
		{
			quote = src[i];
			i++;
		}
		else
		{
			dest[j] = src[i];
			i++;
			j++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

char	*remove_wildcard_quote(char *str)
{
	char	*removed;
	int		size;

	if (!str)
		return (NULL);
	size = get_new_size(str);
	removed = malloc(sizeof(char) * (size + 1));
	if (!removed)
		return (NULL);
	removed = copy_removed(removed, str);
	return (removed);
}
