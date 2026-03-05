/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:52:21 by mzouhir           #+#    #+#             */
/*   Updated: 2026/03/04 18:18:54 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errno.h"

static void	print_error(char *name, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
}

static void	error_handler(char *cmd, char *path, int ret)
{
	if (ret == IS_A_DIRECTORY)
	{
		print_error(cmd, "Is a directory\n");
		exit(126);
	}
	if (ret == PERMISSION_DENIED)
	{
		print_error(cmd, "Permission denied\n");
		exit(126);
	}
	if (ret == COMMAND_NOT_FOUND || path == NULL)
	{
		if (ft_strncmp(cmd, "./", 2) == 0
			|| ft_strncmp(cmd, "/", 1) == 0)
			print_error(cmd, "No such file or directory\n");
		else
			print_error(cmd, "command not found\n");
		exit(127);
	}
}

static void	child_process(t_node *node, t_minishell *data)
{
	char	*path;
	char	**env_tab;
	int		ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redir(node))
		exit(1);
	if (!node->command.argv[0])
		exit(0);
	ret = 0;
	path = find_path(node->command.argv[0], data->env, &ret);
	error_handler(node->command.argv[0], path, ret);
	env_tab = list_to_tab(data->env);
	execve(path, node->command.argv, env_tab);
	free_args(env_tab);
	ft_printf("minishell: %s: %s\n", node->command.argv[0], strerror(errno));
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
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 2);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		return (128 + WTERMSIG(status));
	}
	return (1);
}
