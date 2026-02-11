/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_dispacher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:09:13 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/11 15:52:02 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_built_in(t_node *node)
{
	char	*cmd;

	cmd = node->command.argv[0];
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	built_in_exec(t_node *node, t_minishell *data)
{
	char	*cmd;

	cmd = node->command.argv[0];
	if (!ft_strncmp(cmd, "echo", 5))
		return (ft_echo(node, data));
	if (!ft_strncmp(cmd, "cd", 3))
		return (ft_cd(node, data));
	if (!ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd(data));
	//if (!ft_strncmp(cmd, "export", 7))
	//	return (ft_export(node, data));
	//if (!ft_strncmp(cmd, "unset", 6))
	//	return (ft_unset(node, data));
	if (!ft_strncmp(cmd, "env", 4))
		return (ft_env(data));
	if (!ft_strncmp(cmd, "exit", 5))
		return (ft_exit(node, data));
	return (1);
}
