/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:01:32 by mzouhir           #+#    #+#             */
/*   Updated: 2026/03/04 12:33:38 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig_val;

static void	restore_stdin(int saved_fd, char *line)
{
	dup2(saved_fd, STDIN_FILENO);
	close(saved_fd);
	if (line)
		free(line);
}

static int	heredoc_loop(int fd, t_redir_node *redir)
{
	char	*line;
	int		saved_fd;

	saved_fd = dup(STDIN_FILENO);
	signal(SIGINT, sig_int_heredoc);
	while (1)
	{
		line = readline("heredoc> ");
		if (g_sig_val == 130)
			return (restore_stdin(saved_fd, line), 1);
		if (!line)
		{
			printf("here-document delimited by end-of-file\n");
			break ;
		}
		if (!ft_strncmp(line, redir->filename, ft_strlen(redir->filename) + 1))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (restore_stdin(saved_fd, NULL), signals_handler(), 0);
}

static int	create_heredoc_file(t_redir_node *redir)
{
	static int	i = 0;
	char		*path;
	char		*num;
	int			fd;

	num = ft_itoa(i);
	path = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	i++;
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (1);
	heredoc_loop(fd, redir);
	close(fd);
	free(redir->filename);
	redir->filename = path;
	return (0);
}

static int	heredoc_cmd(t_node *node)
{
	t_redir_node	*tmp;

	tmp = node->command.redir;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
		{
			if (create_heredoc_file(tmp) != 0)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	process_heredoc(t_node *node)
{
	if (!node)
		return (0);
	if (node->node_type == NODE_PIPE || node->node_type == NODE_AND
		|| node->node_type == NODE_OR)
	{
		if (process_heredoc(node->bin_op.first) != 0)
			return (1);
		if (process_heredoc(node->bin_op.second) != 0)
			return (1);
	}
	if (node->node_type == NODE_CMD)
		return (heredoc_cmd(node));
	return (0);
}
