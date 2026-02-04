/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:04:34 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/03 17:24:52 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extract_word(char *input, int len, t_token **list)
{
	char	*word;
	t_token	*new;

	word = ft_substr(input, 0, len);
	if (!word)
		return (0);
	new = create_token(word, WORD);
	if (!new)
	{
		free(word);
		return (0);
	}
	free(word);
	token_add_back(new, list);
	return (1);
}

int	handle_word(char *input, t_token **list)
{
	int		i;

	i = 0;
	while (input[i] && !ft_isspace(input[i]) && !ft_isoperator(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
			i += skip_quotes(input, i);
		else
			i++;
	}
	if (i == -1)
		return (-1);
	if (!extract_word(input, i, list))
		return (-2);
	return (i);
}
