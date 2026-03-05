/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grow_tab_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:56:09 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 13:47:29 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

int	ft_grow_tab_str_exit(t_tab_str *tab_str, char **new_str, int *new_is_op)
{
	free(tab_str->strs);
	free(tab_str->is_op);
	tab_str->strs = new_str;
	tab_str->is_op = new_is_op;
	return (1);
}

int	ft_grow_tab_str(t_tab_str *tab_str, float facteur)
{
	char	**new_str;
	int		*new_is_op;
	size_t	new_cap;
	size_t	i;

	if (tab_str == NULL || tab_str->strs == NULL)
		return (0);
	facteur += (facteur <= 1) * 1;
	new_cap = (size_t)(facteur * tab_str->cap);
	new_str = ft_calloc(new_cap, sizeof(char *));
	if (new_str == NULL)
		return (0);
	new_is_op = ft_calloc(new_cap, sizeof(int));
	if (new_is_op == NULL)
		return (free(new_str), 0);
	i = 0;
	while (i < tab_str->len)
	{
		new_str[i] = tab_str->strs[i];
		new_is_op[i] = tab_str->is_op[i];
		i++;
	}
	tab_str->cap = new_cap;
	return (ft_grow_tab_str_exit(tab_str, new_str, new_is_op));
}
