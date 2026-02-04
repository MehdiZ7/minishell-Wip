/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:36 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/03 18:32:42 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_back(t_env *new, t_env **list)
{
	t_env	*tmp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static t_env	*extract_env(char *env)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = NULL;
	while (env[i] && env[i] != '=')
		i++;
	new->key = ft_substr(env, 0, i);
	if (!new->key)
		return (free(new), NULL);
	if (env[i] == '=')
	{
		i++;
		new->value = ft_substr(env, i, ft_strlen(env) - i);
		if (!new->value)
			return (free(new->key), free(new), NULL);
	}
	new->next = NULL;
	return (new);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		tmp = extract_env(envp[i]);
		if (!tmp)
			return (free_env(env), NULL);
		env_add_back(tmp, &env);
		i++;
	}
	return (env);
}
