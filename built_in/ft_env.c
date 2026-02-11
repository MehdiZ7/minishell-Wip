/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:09:19 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/10 17:28:50 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *data)
{
	t_env	*envp;

	envp = data->env;
	while (envp)
	{
		if (envp->value)
		{
			printf("%s", envp->key);
			printf("=");
			printf("%s", envp->value);
			printf("\n");
		}
		envp = envp->next;
	}
	data->exit_status = 0;
	return (0);
}
