/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tab_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:43:26 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 13:55:14 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	ft_printf_tab_str(t_tab_str *tab)
{
	size_t	i;

	if (tab == NULL)
	{
		ft_printf("tab : NULL\n");
		return ;
	}
	i = 0;
	while (i < tab->len)
	{
		ft_printf("[%ld]/%d: %s\n", i, tab->is_op[i], tab->strs[i]);
		i++;
	}
}
