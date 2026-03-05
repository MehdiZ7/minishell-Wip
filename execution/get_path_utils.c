/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:13:07 by lmilando          #+#    #+#             */
/*   Updated: 2026/03/04 18:30:01 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_env(char *key, char *val)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, val);
	free(tmp);
	return (res);
}

char	**list_to_tab(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*tmp;

	tmp = env;
	envp = lst_utils(env, &i);
	i = 0;
	while (env)
	{
		if (env->value == NULL)
		{
			env = env->next;
			continue ;
		}
		envp[i] = handle_env(env->key, env->value);
		if (!envp[i])
			return (free_args(envp), NULL);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_env(t_env *env, char *var)
{
	while (env)
	{
		if (ft_strlen(env->key) == ft_strlen(var) && strncmp(env->key, var,
				ft_strlen(var)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*build_cmd_path(char *cmd, char *path)
{
	char	*cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (cmd_path);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
