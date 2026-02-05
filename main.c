/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:11:59 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/05 14:01:25 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_data(t_minishell *data)
{
	free_env(data->env);
	data->env = NULL;
	free_token(data->tokens);
	data->tokens = NULL;
	//free_ast TODO
	rl_clear_history();
}

void	clean_exit(t_minishell *data)
{
	cleanup_data(data);
	free(data);
	exit (1);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*data;

	data = init_minishell(envp);
	if (!data)
		return (1);
	(void)ac;
	(void)av;
	(void)data->env;
	//print_env(env);
	if (shell_loop(data) == -1)
		clean_exit(data);
	cleanup_data(data);
	free(data);
	return (0);
}
