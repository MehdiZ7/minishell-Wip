/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:55:59 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/25 10:14:32 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

void	ft_free_tab_str(t_tab_str **p_tab_str)
{
	t_tab_str	*r;
	size_t		i;

	if (p_tab_str == NULL || *p_tab_str == NULL)
		return ;
	r = *p_tab_str;
	i = 0;
	while (r->strs != NULL && i < r->len)
	{
		free(r->strs[i]);
		r->strs[i] = NULL;
		i++;
	}
	free(r->is_op);
	r->is_op = NULL;
	free(r->strs);
	r->strs = NULL;
	free(r);
	*p_tab_str = NULL;
}
