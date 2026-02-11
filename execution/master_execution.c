/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:15:59 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/10 15:28:37 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (0);
}
