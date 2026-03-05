/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_str_to_tab_str.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:55:44 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/22 10:55:46 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

int	ft_append_str_to_tab_str(t_tab_str **p_tab_strs, char *str)
{
	if ((*p_tab_strs)->len >= (*p_tab_strs)->cap)
	{
		if (ft_grow_tab_str(*p_tab_strs, 2.0f) == 0)
			return (0);
	}
	(*p_tab_strs)->strs[(*p_tab_strs)->len] = ft_strdup(str);
	((*p_tab_strs)->len)++;
	return (1);
}
