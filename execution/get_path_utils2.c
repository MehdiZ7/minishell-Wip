/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:24:38 by mzouhir           #+#    #+#             */
/*   Updated: 2026/03/04 18:30:49 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_utils(t_env *env, int *i)
{
	t_env	*tmp;
	char	**envp;

	*i = 0;
	tmp = env;
	while (tmp)
	{
		(*i)++;
		tmp = tmp->next;
	}
	envp = ft_calloc(sizeof(char *), (*i + 1));
	if (!envp)
		return (NULL);
	return (envp);
}
