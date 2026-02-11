/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:32:31 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/10 16:14:35 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag_valid(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

int	ft_echo(t_node *node, t_minishell *data)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 1;
	while (node->command.argv[i] && is_flag_valid(node->command.argv[i]))
	{
		i++;
		n_flag = true;
	}
	while (node->command.argv[i])
	{
		printf("%s", node->command.argv[i]);
		if (node->command.argv[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag == false)
		printf("\n");
	data->exit_status = 0;
	return (0);
}
