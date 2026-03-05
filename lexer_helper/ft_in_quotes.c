/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:30:02 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/22 11:34:07 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

void	ft_in_quotes(char *str, size_t pos, int *ret)
{
	size_t	i;

	i = 0;
	*ret = 0;
	while (str[i] && i <= pos)
	{
		if (*ret == NOT_IN_QUOTES)
		{
			if (str[i] == '"')
				*ret = IN_DOUBLE_QUOTES;
			else if (str[i] == '\'')
				*ret = IN_SIMPLE_QUOTES;
		}
		else
		{
			if (str[i] == '"' && *ret == IN_DOUBLE_QUOTES)
				*ret = NOT_IN_QUOTES;
			else if (str[i] == '\'' && *ret == IN_SIMPLE_QUOTES)
				*ret = NOT_IN_QUOTES;
		}
		i++;
	}
}
