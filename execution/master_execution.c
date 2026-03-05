/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:15:59 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/25 12:21:51 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_and(t_node *node, t_minishell *data)
{
	int	status;

	status = executor(node->bin_op.first, data);
	if (status == 0)
		return (executor(node->bin_op.second, data));
	return (status);
}

static int	exec_or(t_node *node, t_minishell *data)
{
	int	status;

	status = executor(node->bin_op.first, data);
	if (status != 0)
		return (executor(node->bin_op.second, data));
	return (status);
}

int	executor(t_node *node, t_minishell *data)
{
	if (node == NULL)
		return (0);
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
