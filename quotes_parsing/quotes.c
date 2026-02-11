/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:47:16 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/09 11:47:25 by mzouhir          ###   ########.fr       */
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

int	remove_quote(t_minishell *data)
{
	t_token	*token;
	char	*removed;
	int		size;

	token = data->tokens;
	while (token)
	{
		if (token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
		{
			size = get_new_size(token->value);
			removed = malloc(sizeof(char) * (size + 1));
			if (!removed)
				return (-1);
			removed = copy_removed(removed, token->value);
			free(token->value);
			token->value = removed;
		}
		token = token->next;
	}

	return (1);
}
