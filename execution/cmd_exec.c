/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:52:21 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/23 13:34:36 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *name)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
}

static void	child_process(t_node *node, t_minishell *data)
{
	char	*path;

	if (handle_redir(node))
		exit(1);
	if (!node->command.argv[0])
		exit(0);
	path = find_path(node->command.argv[0], data->env);
	if (!path)
	{
		print_error(node->command.argv[0]);
		exit(127);
	}
	execve(path, node->command.argv, list_to_tab(data->env));
	perror("execve: ");
	exit(126);
}

int	exec_cmd(t_node *node, t_minishell *data)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork: "), 1);
	if (pid == 0)
		child_process(node, data);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
