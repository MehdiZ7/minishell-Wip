/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:01:07 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/10 11:48:04 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_tab(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(envp[i], env->value);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (NULL);
}

char	*get_env(t_env *env)
{
	while (env)
	{
		if (!strncmp(env->key, "PATH", 5))
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

char	*find_path(char *cmd, t_env *env)
{
	char	*cmd_path;
	char	*env_path;
	char	**path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
	}
	env_path = get_env(env);
	if (!env_path)
		return (NULL);
	path = ft_split(env_path, ':');
	while (path[i])
	{
		cmd_path = build_cmd_path(cmd, path[i]);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (free_split(path), cmd_path);
		free(cmd_path);
		i++;
	}
	free_split(path);
	return (NULL);
}
