/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:22:32 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/09 15:49:45 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe1(int *fd, t_node *node, t_minishell *data)
{
	int	exit_code;

	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
	exit_code = executor(node->pipe_command.first, data);
	exit(exit_code);
}

void	pipe2(int *fd, t_node *node, t_minishell *data)
{
	int	exit_code;

	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	exit_code = executor(node->pipe_command.second, data);
	exit(exit_code);
}

int	exec_pipe(t_node *node, t_minishell *data)
{
	int		fd[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		return (perror ("pipe"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (close(fd[0]), close(fd[1]), perror("fork"), 1);
	if (pid1 == 0)
		pipe1(fd, node, data);
	pid2 = fork();
	if (pid2 == -1)
		return (close(fd[0]), close(fd[1]), perror("fork"),
			waitpid(pid1, NULL, 0), 1);
	if (pid2 == 0)
		pipe2(fd, node, data);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}



