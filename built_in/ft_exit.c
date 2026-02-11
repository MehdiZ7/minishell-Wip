/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:26:18 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/11 13:55:44 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	clean_exit(t_minishell *data)
{
	rl_clear_history();
	if (data->ast)
		free_ast_node(data->ast);
	if (data->env)
		free_env(data->env);
	if (data->tokens)
		free_token(data->tokens);
	if (data)
		free(data);
}

int	ft_exit(t_node *node, t_minishell *data)
{
	int	ret;

	printf("exit\n");
	if (node->command.argv[1])
	{
		if (!is_valid(node->command.argv[1]))
		{
			printf("exit: %s numeric argument required\n",
				node->command.argv[1]);
			clean_exit(data);
			exit(255);
		}
		if (node->command.argv[2])
		{
			printf("exit: too many arguments\n");
			data->exit_status = 1;
			return (1);
		}
		ret = ft_atoi(node->command.argv[1]) % 256;
		clean_exit(data);
		exit(ret);
	}
	ret = data->exit_status;
	clean_exit(data);
	return (exit(ret), 0);
}
