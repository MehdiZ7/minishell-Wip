/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:28:26 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/08 21:16:17 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_var(char *str)
{
	int		i;
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_double == false)
			in_single = !in_single;
		else if (str[i] == '"' && in_single == false)
			in_double = !in_double;
		if (str[i] == '$' && in_single == false)
		{
			if (str[i + 1] && (ft_isalnum(str[i + 1])
					|| str[i + 1] == '_' || str[i + 1] == '?'))
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*extract_key(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (ft_substr(str, 0, 1));
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (ft_substr(str, 0, i));

}


int	get_expansion(t_minishell *data)
{
	t_token	*token;
	char	*key;
	int		index;

	index = -1;
	token = data->tokens;
	while (token)
	{
		if (token->type == DOUBLE_QUOTE || token->type == ENV)
		{
			index = check_for_var(token->value);
			if (index >= 0)
			{
				key = extract_key(token->value + index + 1);
				if (!key)
					return (-1);
				if (replace_var(token, key, index, data) == -1)
					return (free(key), -1);
				free(key);
				continue ;
			}
		}
		token = token->next;
	}
	return (0);
}
