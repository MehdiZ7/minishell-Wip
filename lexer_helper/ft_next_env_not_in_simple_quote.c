/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_env_not_in_simple_quote.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:56:14 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 13:52:41 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

ssize_t	ft_next_env_not_in_simple_quote(char *str, size_t pos)
{
	int	in_simple_quote;
	int	in_double_quote;

	if (ft_strlen(str) <= pos)
		return (-1);
	in_simple_quote = 0;
	in_double_quote = 0;
	while (str[pos])
	{
		if (in_double_quote == 0 && in_simple_quote == 0)
		{
			in_double_quote = (str[pos] == '"');
			in_simple_quote = (str[pos] == '\'');
		}
		else if (str[pos] == '"' && in_double_quote == 1)
			in_double_quote = 0;
		else if (str[pos] == '\'' && in_simple_quote == 1)
			in_simple_quote = 0;
		if (str[pos] == '$' && (ft_isalnum(str[pos + 1]) || str[pos + 1] == '_'
				|| str[pos + 1] == '?') && in_simple_quote == 0)
			return (pos);
		pos++;
	}
	return (-1);
}
