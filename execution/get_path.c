/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:01:07 by mzouhir           #+#    #+#             */
/*   Updated: 2026/03/04 13:35:40 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_absolute_path(char *cmd, int *ret)
{
	struct stat	stat_buf;

	lstat(cmd, &stat_buf);
	if (S_ISDIR(stat_buf.st_mode) == 1)
	{
		*ret = IS_A_DIRECTORY;
		return (NULL);
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	return (NULL);
}

static char	*find_relative_path(char *cmd, t_env *env, int *ret)
{
	char		*env_path;
	char		*cmd_path;
	struct stat	stat_buf;

	*ret = COMMAND_NOT_FOUND;
	env_path = get_env(env, "PWD");
	if (!env_path)
		return (NULL);
	cmd_path = ft_strjoin(env_path, &cmd[1]);
	free(env_path);
	if (cmd_path == NULL)
		return (NULL);
	if (access(cmd_path, F_OK | X_OK) == 0)
	{
		*ret = 0;
		return (cmd_path);
	}
	else if (access(cmd_path, F_OK) == 0)
		*ret = PERMISSION_DENIED;
	lstat(cmd, &stat_buf);
	if (S_ISDIR(stat_buf.st_mode) == 1 && *ret == 0)
		*ret = IS_A_DIRECTORY;
	free(cmd_path);
	return (NULL);
}

static char	*find_path_loop(char **path, int i, char *cmd, int *ret)
{
	char		*cmd_path;
	struct stat	stat_buf;

	cmd_path = build_cmd_path(cmd, path[i]);
	if (access(cmd_path, F_OK | X_OK) == 0)
	{
		*ret = 0;
		return (free_split(path), cmd_path);
	}
	else if (access(cmd_path, F_OK) == 0)
		*ret = PERMISSION_DENIED;
	lstat(cmd, &stat_buf);
	if (S_ISDIR(stat_buf.st_mode) == 1 && *ret == 0)
		*ret = IS_A_DIRECTORY;
	free(cmd_path);
	return ((void *)0x1);
}

char	*find_path(char *cmd, t_env *env, int *ret)
{
	char		*cmd_path;
	char		*env_path;
	char		**path;
	int			i;

	i = 0;
	if (cmd[0] == '/')
		return (find_absolute_path(cmd, ret));
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (find_relative_path(cmd, env, ret));
	*ret = COMMAND_NOT_FOUND;
	env_path = get_env(env, "PATH");
	if (!env_path)
		return (NULL);
	path = ft_split(env_path, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		cmd_path = find_path_loop(path, i, cmd, ret);
		if (cmd_path != (void *)0x1)
			return (cmd_path);
		i++;
	}
	return (free_split(path), NULL);
}
