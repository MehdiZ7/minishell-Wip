/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:07:50 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/28 23:03:57 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(char *dest, char *old_pwd, t_minishell *data)
{
	int	ret;

	ret = chdir(dest);
	if (ret != 0)
	{
		free(old_pwd);
		perror("cd: ");
		data->exit_status = 1;
		return (1);
	}
	if (!old_pwd)
		update_env("OLDPWD", "", data);
	else if (old_pwd)
		update_env("OLDPWD", old_pwd, data);
	dest = getcwd(NULL, 0);
	if (dest)
		update_env("PWD", dest, data);
	else
		ft_putstr_fd("cd : error retrieving current directory\n", STDERR_FILENO);
	if (dest)
		free(dest);
	free(old_pwd);
	data->exit_status = 0;
	return (0);
}

static char	*get_value(char *key, t_minishell *data)
{
	t_env	*envp;

	envp = data->env;
	while (envp)
	{
		if (!ft_strncmp(key, envp->key, ft_strlen(envp->key) + 1))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

char	*get_target(t_node *node, t_minishell *data)
{
	char	*dest;

	if (!node->command.argv[1])
	{
		dest = get_value("HOME", data);
		if (!dest)
			return (ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO), NULL);
	}
	else if (!ft_strncmp(node->command.argv[1], "-", 2))
	{
		dest = get_value("OLDPWD", data);
		if (!dest)
			return (ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO), NULL);
		ft_printf("%s\n", dest);
	}
	else
		dest = node->command.argv[1];
	return (dest);
}

static char	*get_old_pwd(t_minishell *data)
{
	char	*old_pwd;
	char	*tmp;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		tmp = get_value("PWD", data);
		if (tmp)
			old_pwd = ft_strdup(tmp);
		else
			old_pwd = NULL;
	}
	return (old_pwd);
}

int	ft_cd(t_node *node, t_minishell *data)
{
	char	*old_pwd;
	char	*dest;

	if (node->command.argv[1] && node->command.argv[2])
	{
		data->exit_status = 1;
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	old_pwd = get_old_pwd(data);
	dest = get_target(node, data);
	if (!dest)
	{
		if (old_pwd)
			free(old_pwd);
		data->exit_status = 1;
		return (1);
	}
	if (!update_pwd(dest, old_pwd, data))
		return (0);
	return (1);
}
