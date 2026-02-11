/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:04:24 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/11 16:05:08 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(char *key, char *value, t_minishell *data)
{
	t_env	*envp;

	envp = data->env;
	while (envp)
	{
		if (!ft_strncmp(key, envp->key, ft_strlen(envp->key) + 1))
		{
			free(envp->value);
			envp->value = ft_strdup(value);
			if (!envp->value)
				return (-1);
			return (0);
		}
		envp = envp->next;
	}
	if (create_new(key, value, data) != 0)
		return (-1);
	return (0);
}

int	create_new(char *key, char *value, t_minishell *data)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->next = NULL;
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (-1);
	}
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (-1);
	}
	env_add_back(new, &data->env);
	return (0);
}
