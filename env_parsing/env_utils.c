/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:08:30 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/05 14:02:10 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		if (env->value)
			free(env->value);
		if (env->key)
			free(env->key);
		env = env->next;
		free(tmp);
		tmp = NULL;
	}
	free(env);
	env = NULL;
}
