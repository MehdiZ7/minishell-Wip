/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:11:59 by mzouhir           #+#    #+#             */
/*   Updated: 2026/03/03 14:30:01 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig_val;

void	cleanup_data(t_minishell *data)
{
	free_env(data->env);
	data->env = NULL;
	free_token(data->tokens);
	data->tokens = NULL;
	rl_clear_history();
}

void	clean_exit(t_minishell *data)
{
	int	status;

	status = data->exit_status;
	cleanup_data(data);
	free(data);
	exit(status);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*data;
	t_ttyctx	tty;

	(void)ac;
	(void)av;
	if (ttyctx_init(&tty) != 0)
		return (EXIT_FAILURE);
	rl_catch_signals = 0;
	data = init_minishell(envp);
	if (!data)
		return (1);
	if (shell_loop(data, &tty) == -1)
		clean_exit(data);
	cleanup_data(data);
	free(data);
	return (0);
}
