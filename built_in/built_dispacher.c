/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_dispacher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:09:13 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/27 10:40:28 by lmilando         ###   ########.fr       */
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

static int	built_in_dispatch(t_node *node, t_minishell *data)
{
	char	*cmd;

	cmd = node->command.argv[0];
	if (!ft_strncmp(cmd, "echo", 5))
		return (ft_echo(node, data));
	if (!ft_strncmp(cmd, "cd", 3))
		return (ft_cd(node, data));
	if (!ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd(data));
	if (!ft_strncmp(cmd, "export", 7))
		return (ft_export(node, data));
	if (!ft_strncmp(cmd, "unset", 6))
		return (ft_unset(node, data));
	if (!ft_strncmp(cmd, "env", 4))
		return (ft_env(node, data));
	if (!ft_strncmp(cmd, "exit", 5))
		return (ft_exit(node, data));
	return (1);
}

int	built_in_exec(t_node *node, t_minishell *data)
{
	int	status;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redir(node))
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	status = built_in_dispatch(node, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}
