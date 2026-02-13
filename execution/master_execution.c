/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:15:59 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/13 13:56:50 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_and(t_node *node, t_minishell *data)
{
	int	status;

	status = executor(node->and_command.first, data);
	if (status == 0)
		return (executor(node->and_command.second, data));
	return (status);
}

static int	exec_or(t_node *node, t_minishell *data)
{
	int	status;

	status = executor(node->or_command.first, data);
	if (status != 0)
		return (executor(node->or_command.second, data));
	return (status);
}

int	executor(t_node *node, t_minishell *data)
{
	if (node->node_type == NODE_CMD)
	{
		if (check_for_built_in(node))
			return (built_in_exec(node, data));
		return (exec_cmd(node, data));
	}
	if (node->node_type == NODE_PIPE)
		return (exec_pipe(node, data));
	if (node->node_type == NODE_AND)
		return (exec_and(node, data));
	if (node->node_type == NODE_OR)
		return (exec_or(node, data));
	return (0);
}
