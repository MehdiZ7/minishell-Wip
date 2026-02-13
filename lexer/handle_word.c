/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:04:34 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/11 21:31:14 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(char *input, t_token **list)
{
	int					len;
	enum e_token_type	token_type;
	char				*word;
	t_token				*new;

	len = 1;
	token_type = (input[0] == '\'') * SINGLE_QUOTE + (input[0] == '"')
			* DOUBLE_QUOTE;
	if (token_type == 0)
		return (-1);
	while (input[len] && input[len] != '"' && input[len] != '\'')
		len++;
	if (len == 0)
		return (len);
	if (input[len] == 0)
		return (-1);
	if (input[len] == '\'' && token_type == DOUBLE_QUOTE)
		return (-1);
	if (input[len] == '"' && token_type == SINGLE_QUOTE)
		return (-1);
	word = ft_substr(input, 0, len);
	if (!word)
		return (0);
	new = create_token(word, token_type);
	free(word);
	if (!new)
		return (0);
	token_add_back(new, list);
	return (len + 1);
}

int	handle_cmd_or_arg(char *input, t_token **list)
{
	char				*word;
	t_token				*new;
	enum e_token_type	token_type;
	size_t				len;

	len = 0;
	while (input[len] && !ft_isspace(input[len]) && !ft_isseparator(input[len])
		&& input[len] != '(' && input[len] != ')')
		len++;
	if (len == 0)
		return (len);
	word = ft_substr(input, 0, len);
	if (!word)
		return (0);
	token_type = CMD_OR_ARG;
	if (input[0] == '$')
		token_type = ENV;
	new = create_token(word, token_type);
	free(word);
	if (!new)
		return (0);
	token_add_back(new, list);
	return (len);
}
