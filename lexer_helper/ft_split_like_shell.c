/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_like_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:38:33 by lmilando          #+#    #+#             */
/*   Updated: 2026/03/01 12:48:59 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

static void	*split_on_operator(char *str, size_t *p_last_pos, size_t *p_i,
		t_tab_str **p_ret)
{
	size_t	op_end;

	while (str[*p_last_pos] == ' ')
		(*p_last_pos)++;
	if (*p_i > (*p_last_pos))
	{
		if (append_helper(p_ret, str, *p_last_pos, *p_i - *p_last_pos) == NULL)
			return (NULL);
		*p_last_pos = *p_i;
	}
	op_end = get_operator_end(str, *p_i);
	if (append_helper(p_ret, str, *p_i, op_end - *p_i) == NULL)
		return (NULL);
	(*p_ret)->is_op[(*p_ret)->len - 1] = 1;
	*p_i = op_end;
	*p_last_pos = *p_i;
	return ((void *)0x1);
}

static void	*ft_init_split_like_shell(t_tab_str **p_ret, size_t *p_i,
		size_t *p_last_pos, int *p_quote)
{
	*p_ret = ft_calloc(1, sizeof(t_tab_str));
	if (*p_ret == NULL)
		return (NULL);
	(*p_ret)->cap = 16;
	(*p_ret)->strs = ft_calloc((*p_ret)->cap, sizeof(char *));
	if ((*p_ret)->strs == NULL)
		return (ft_free_tab_str(p_ret), NULL);
	(*p_ret)->is_op = ft_calloc((*p_ret)->cap, sizeof(int));
	if ((*p_ret)->is_op == NULL)
		return (ft_free_tab_str(p_ret), NULL);
	*p_i = 0;
	*p_last_pos = 0;
	*p_quote = NOT_IN_QUOTES;
	return ((void *)0x1);
}

static void	*split_on_first_space(char *str, size_t *p_last_pos, size_t *p_i,
		t_tab_str **p_ret)
{
	while (str[*p_last_pos] == ' ')
		(*p_last_pos)++;
	if (*p_i > *p_last_pos)
	{
		if (append_helper(p_ret, str, *p_last_pos, *p_i - *p_last_pos) == NULL)
			return (NULL);
		*p_last_pos = *p_i;
	}
	return ((void *)0x1);
}

t_tab_str	*ft_split_like_shell(char *str)
{
	t_tab_str	*ret;
	size_t		i;
	int			quote;
	size_t		last_pos;

	if (ft_init_split_like_shell(&ret, &i, &last_pos, &quote) == NULL)
		return (NULL);
	while (i < ft_strlen(str) && str[i])
	{
		ft_in_quotes(str, i, &quote);
		if (quote == NOT_IN_QUOTES && is_split_operator(str[i])
			&& split_on_operator(str, &last_pos, &i, &ret) == NULL)
			return (NULL);
		if (quote == NOT_IN_QUOTES && str[i] == ' ' && i != last_pos
			&& split_on_first_space(str, &last_pos, &i, &ret) == NULL)
			return (NULL);
		i++;
	}
	while (str[last_pos] == ' ')
		last_pos++;
	if (str[last_pos] && i > last_pos && append_helper(&ret, str, last_pos, i
			- last_pos) == NULL)
		return (NULL);
	return (ret);
}
