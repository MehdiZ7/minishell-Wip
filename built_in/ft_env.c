/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:09:19 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/28 23:06:16 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_node *node, t_minishell *data)
{
	t_env	*envp;

	if (node->command.argv[1])
	{
		data->exit_status = 0;
		return (0);
	}
	envp = data->env;
	while (envp)
	{
		if (envp->value)
		{
			ft_printf("%s", envp->key);
			ft_printf("=");
			ft_printf("%s", envp->value);
			ft_printf("\n");
		}
		envp = envp->next;
	}
	data->exit_status = 0;
	return (0);
}
