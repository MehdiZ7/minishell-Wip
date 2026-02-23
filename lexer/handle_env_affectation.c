/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_affectation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:02:45 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/18 17:13:32 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_affect_len(char *input)
{
	size_t	len;
	int		nbr_double_quotes;

	len = 0;
	nbr_double_quotes = 0;
	while (input[len])
	{
		if (nbr_double_quotes == 0 && (ft_isseparator(input[len])
				|| ft_isspace(input[len])))
			break ;
		nbr_double_quotes += (input[len] == '"');
		if (nbr_double_quotes == 2)
			break ;
		len++;
	}
	return (len);
}

int	handle_env_affectation(char *input, t_token **list)
{
	char				*word;
	t_token				*new;
	enum e_token_type	token_type;
	size_t				len;

	len = env_affect_len(input);
	if (len == 0)
		return (len);
	word = ft_substr(input, 0, len);
	if (!word)
		return (0);
	token_type = CMD_OR_ARG;
	new = create_token(word, token_type);
	free(word);
	if (!new)
		return (0);
	token_add_back(new, list);
	return (len);
}
