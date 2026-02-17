/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:11:59 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/14 10:11:40 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_data(t_minishell *data)
{
	free_env(data->env);
	data->env = NULL;
	free_token(data->tokens);
	data->tokens = NULL;
	// free_ast TODO
	rl_clear_history();
}

void	clean_exit(t_minishell *data)
{
	cleanup_data(data);
	free(data);
	exit(1);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*data;

	(void)ac;
	(void)av;
	data = init_minishell(envp);
	if (!data)
		return (1);
	if (shell_loop(data) == -1)
		clean_exit(data);
	//test_exec(data);
	//test_pipe_exec(data);
	//check_heredoc(data);
	//test_builtins(data);
	cleanup_data(data);
	free(data);
	return (0);
}
