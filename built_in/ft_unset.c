/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:56:47 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/13 13:22:20 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_env *prev, t_env *current, t_minishell *data)
{
	if (!prev)
	{
		data->env = data->env->next;
		free(current->value);
		free(current->key);
		free(current);
	}
	else
	{
		prev->next = current->next;
		free(current->value);
		free(current->key);
		free(current);
	}
}

int	ft_unset(t_node *node, t_minishell *data)
{
	int		i;
	t_env	*current;
	t_env	*prev;

	i = 1;
	while (node->command.argv[i])
	{
		prev = NULL;
		current = data->env;
		while (current)
		{
			if (!ft_strncmp(node->command.argv[i], current->key
					, ft_strlen(current->key) + 1))
			{
				delete_node(prev, current, data);
				break ;
			}
					prev = current;
					current = current->next;
		}
		i++;
	}
	data->exit_status = 0;
	return (0);
}
