/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grow_last_str_of_tab_str.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:56:04 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/22 10:56:06 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

int	ft_grow_last_str_of_tab_str(t_tab_str **p_tab_strs, char *str)
{
	char	*temp;
	char	*last;
	char	*append;

	if ((*p_tab_strs)->len == 0)
		return (0);
	last = (*p_tab_strs)->strs[(*p_tab_strs)->len - 1];
	if (last == NULL)
	{
		last = ft_strdup(str);
		if (last == NULL)
			return (0);
		return (1);
	}
	append = ft_strdup(str);
	if (append == NULL)
		return (0);
	temp = ft_strjoin(last, append);
	if (temp == NULL)
		return (free(append), 0);
	free(append);
	free(last);
	(*p_tab_strs)->strs[(*p_tab_strs)->len - 1] = temp;
	return (1);
}
