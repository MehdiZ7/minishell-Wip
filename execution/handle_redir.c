/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:34:57 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/23 13:35:10 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_file(t_redir_node *redir)
{
	if (redir->type == REDIR_IN_FILE)
		return (open(redir->filename, O_RDONLY));
	if (redir->type == REDIR_OUT_FILE)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == REDIR_APPEND)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

int	handle_redir_heredoc(t_redir_node *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	dup2(fd, 0);
	unlink(redir->filename);
	close(fd);
	return (0);
}

int	handle_redir(t_node *node)
{
	t_redir_node	*tmp;
	int				fd;

	tmp = node->command.redir;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
		{
			if (handle_redir_heredoc(tmp))
				return (1);
		}
		else if (tmp->type != REDIR_HEREDOC)
		{
			fd = open_redir_file(tmp);
			if (fd == -1)
				return (perror("filename: "), 1);
			if (tmp->type == REDIR_IN_FILE)
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close (fd);
		}
		tmp = tmp->next;
	}
	return (0);
}
