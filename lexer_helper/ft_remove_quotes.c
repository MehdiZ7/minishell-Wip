/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:56:24 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 16:04:14 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

static void	ft_remove_quotes_loop(char *p_c, int *p_in_double_quote,
		int *p_in_simple_quote)
{
	if ((*p_in_double_quote) == 0 && (*p_in_simple_quote) == 0)
	{
		if (*p_c == '"')
		{
			*p_c = 0;
			(*p_in_double_quote) = 1;
		}
		else if (*p_c == '\'')
		{
			*p_c = 0;
			(*p_in_simple_quote) = 1;
		}
	}
	else if (*p_c == '"' && (*p_in_double_quote) == 1)
	{
		*p_c = 0;
		(*p_in_double_quote) = 0;
	}
	else if (*p_c == '\'' && (*p_in_simple_quote) == 1)
	{
		*p_c = 0;
		(*p_in_simple_quote) = 0;
	}
}

void	ft_remove_quotes(char *str)
{
	size_t	i;
	size_t	j;
	int		in_simple_quote;
	int		in_double_quote;
	size_t	len;

	if (str == NULL)
		return ;
	len = ft_strlen(str);
	i = 0;
	in_simple_quote = 0;
	in_double_quote = 0;
	while (str[i])
		ft_remove_quotes_loop(&str[i++], &in_double_quote, &in_simple_quote);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != 0)
			str[j++] = str[i];
		i++;
	}
	while (j < len)
		str[j++] = 0;
}
