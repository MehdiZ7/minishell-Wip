/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_string_treatment.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:55:23 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 13:57:03 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

t_tab_str	*ft_complete_string_treatment_helper(t_env *env, t_tab_str *tmp,
		int exit_status, t_tab_str **p_tab_strs)
{
	size_t	i;
	int		ret;

	i = 0;
	while (i < tmp->len)
	{
		ret = ft_not_special_str(p_tab_strs, tmp->strs[i]);
		if (ret == 1)
			(*p_tab_strs)->is_op[(*p_tab_strs)->len - 1] = tmp->is_op[i];
		if (ret == -1)
			return (free_env(env), ft_free_tab_str(p_tab_strs), NULL);
		if (ret == 0)
			ret = ft_replace_env(p_tab_strs, tmp->strs[i], env, exit_status);
		i++;
	}
	i = 0;
	while (i < (*p_tab_strs)->len)
	{
		ft_remove_quotes((*p_tab_strs)->strs[i]);
		i++;
	}
	return (*p_tab_strs);
}

t_tab_str	*ft_complete_string_treatment(t_env *env, t_tab_str *tmp,
		int exit_status)
{
	t_tab_str	*tab_strs;

	tab_strs = ft_calloc(1, sizeof(t_tab_str));
	if (tab_strs == NULL)
		return (free_env(env), NULL);
	tab_strs->cap = STRS_CAP;
	tab_strs->strs = ft_calloc(tab_strs->cap, sizeof(char *));
	if (tab_strs->strs == NULL)
		return (free_env(env), ft_free_tab_str(&tab_strs), NULL);
	tab_strs->is_op = ft_calloc(tab_strs->cap, sizeof(int));
	if (tab_strs->is_op == NULL)
		return (free_env(env), ft_free_tab_str(&tab_strs), NULL);
	return (ft_complete_string_treatment_helper(env, tmp, exit_status,
			&tab_strs));
}
