/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:56:30 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 19:41:11 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

static int	ft_replace_exit_status(t_replace_env r)
{
	r.temp_str = ft_itoa(r.exit_status);
	if (r.temp_str == NULL)
		return (-1);
	if (*(r.p_first) == 0 && ft_append_str_to_tab_str(r.p_tab_strs,
			r.temp_str) == 0)
		return (free(r.temp_str), -1);
	else if (*(r.p_first) != 0 && ft_grow_last_str_of_tab_str(r.p_tab_strs,
			r.temp_str) == 0)
		return (free(r.temp_str), -1);
	free(r.temp_str);
	*(r.p_first) = 1;
	*(r.p_last_pos) = *(r.p_pos) + 1;
	*(r.p_pos) = ft_next_env_not_in_simple_quote(r.str, *(r.p_pos) + 2);
	if (*(r.p_pos) != -1)
		r.temp_str = ft_substr(r.str, *(r.p_last_pos) + 1, *(r.p_pos)
				- *(r.p_last_pos) - 1);
	else
		r.temp_str = ft_substr(r.str, *(r.p_last_pos) + 1, ft_strlen(r.str)
				- *(r.p_last_pos) - 1);
	if (r.temp_str == NULL || ft_grow_last_str_of_tab_str(r.p_tab_strs,
			r.temp_str) == 0)
		return (free(r.temp_str), -1);
	*(r.p_env) = r.env_head;
	return (free(r.temp_str), 0);
}

static int	ft_replace_env_not_found(t_replace_env r)
{
	char	*temp_str;

	if (*(r.p_env) == NULL)
	{
		*(r.p_env) = r.env_head;
		*(r.p_last_pos) = *(r.p_pos) + ft_strlen_env(&((r.str)[*(r.p_pos)
					+ 1]));
		*(r.p_pos) = ft_next_env_not_in_simple_quote(r.str, *(r.p_pos)
				+ ft_strlen_env(&((r.str)[*(r.p_pos) + 1])));
		if (*(r.p_pos) != -1)
			temp_str = ft_substr(r.str, *(r.p_last_pos) + 1, *(r.p_pos)
					- *(r.p_last_pos) - 1);
		else
			temp_str = ft_substr(r.str, *(r.p_last_pos) + 1, ft_strlen(r.str)
					- *(r.p_last_pos) - 1);
		if (temp_str == NULL)
			return (-1);
		if (ft_grow_last_str_of_tab_str(r.p_tab_strs, temp_str) == 0)
			return (free(temp_str), -1);
		free(temp_str);
		temp_str = NULL;
	}
	return (0);
}

static int	ft_replace_env_found(t_replace_env r)
{
	if (*(r.p_first) == 0 && ft_append_str_to_tab_str(r.p_tab_strs,
			(*r.p_env)->value) == 0)
		return (-1);
	else if (*(r.p_first) != 0 && ft_grow_last_str_of_tab_str(r.p_tab_strs,
			(*r.p_env)->value) == 0)
		return (-1);
	*(r.p_first) = 1;
	*(r.p_env) = r.env_head;
	*(r.p_last_pos) = *(r.p_pos) + ft_strlen_env(&(r.str)[*(r.p_pos) + 1]);
	*(r.p_pos) = ft_next_env_not_in_simple_quote(r.str, *(r.p_pos)
			+ ft_strlen_env(&((r.str)[*(r.p_pos) + 1])));
	if (*(r.p_pos) != -1)
		r.temp_str = ft_substr(r.str, *(r.p_last_pos) + 1, *(r.p_pos)
				- *(r.p_last_pos) - 1);
	else
		r.temp_str = ft_substr(r.str, *(r.p_last_pos) + 1, ft_strlen(r.str)
				- *(r.p_last_pos) - 1);
	if (r.temp_str == NULL)
		return (-1);
	if (ft_grow_last_str_of_tab_str(r.p_tab_strs, r.temp_str) == 0)
		return (free(r.temp_str), -1);
	free(r.temp_str);
	return (0);
}

static int	ft_replace_env_loop(t_replace_env r)
{
	while (*(r.p_pos) != -1)
	{
		if ((r.str)[*(r.p_pos) + 1] == '?')
		{
			if (ft_replace_exit_status(r) == -1)
				return (-1);
			continue ;
		}
		if (*(r.p_env) == NULL)
			*(r.p_env) = r.env_head;
		if (ft_strlen_env((*(r.p_env))->key) == \
		ft_strlen_env(&((r.str)[*(r.p_pos)
					+ 1])) && ft_strncmp((*(r.p_env))->key, &((r.str)[*(r.p_pos)
					+ 1]), ft_strlen_env((*(r.p_env))->key)) == 0)
		{
			if (ft_replace_env_found(r) == -1)
				return (-1);
		}
		else
			*r.p_env = (*(r.p_env))->next;
		if (*(r.p_env) == NULL && ft_replace_env_not_found(r) == -1)
			return (-1);
	}
	return (-1);
}

int	ft_replace_env(t_tab_str **p_tab_strs, char *str, t_env *env,
		int exit_status)
{
	ssize_t	pos;
	size_t	last_pos;
	int		first;
	t_env	*env_head;
	char	*temp_str;

	if (ft_next_env_not_in_simple_quote(str, 0) == -1)
		return (0);
	pos = ft_next_env_not_in_simple_quote(str, 0);
	first = 0;
	if (pos != 0)
	{
		temp_str = ft_substr(str, 0, pos);
		if (temp_str == NULL)
			return (-1);
		if (ft_append_str_to_tab_str(p_tab_strs, temp_str) == 0)
			return (free(temp_str), -1);
		first = 1;
		free(temp_str);
	}
	last_pos = 0;
	env_head = env;
	temp_str = NULL;
	return (ft_replace_env_loop((t_replace_env){&pos, &last_pos, &first,
			env_head, &env, p_tab_strs, str, exit_status, NULL}));
}
