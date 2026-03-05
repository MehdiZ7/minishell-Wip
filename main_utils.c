/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:32:42 by mzouhir           #+#    #+#             */
/*   Updated: 2026/03/04 14:03:09 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*data;

	data = malloc(sizeof(t_minishell));
	if (!data)
		return (NULL);
	data->tokens = NULL;
	data->exit_status = 0;
	data->ast = NULL;
	data->env = init_env(envp);
	if (!data->env)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

static void	token_helper(t_token *tok)
{
	while (tok)
	{
		if (tok->type == ENV || tok->type == SINGLE_QUOTE
			|| tok->type == DOUBLE_QUOTE)
			tok->type = CMD_OR_ARG;
		tok = tok->next;
	}
}

static int	shell_loop_helper(char *input, t_minishell *data)
{
	data->tokens = lexer(input, data->env, data->exit_status);
	if (data->tokens == NULL)
		return (free(input), 0);
	if (expand_wildcard(data) == -1)
		return (cleanup_data(data), -1);
	free(input);
	token_helper(data->tokens);
	data->ast = create_ast(data);
	free_token(data->tokens);
	data->tokens = NULL;
	if (process_heredoc(data->ast) != 0)
	{
		free_ast_node(data->ast);
		return (0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (data->ast != NULL)
		data->exit_status = executor(data->ast, data);
	free_ast_node(data->ast);
	return (0);
}

static char	*read_prompt(t_minishell *data, t_ttyctx *tty)
{
	char	*input;

	signals_handler();
	tty_disable_ctrl_backslash(tty);
	g_sig_val = 0;
	input = readline("minishell>$ ");
	if (g_sig_val == 130)
	{
		data->exit_status = 130;
		g_sig_val = 0;
	}
	return (input);
}

int	shell_loop(t_minishell *data, t_ttyctx *tty)
{
	char	*input;

	while (1)
	{
		input = read_prompt(data, tty);
		if (!input)
			return (ft_putstr_fd("exit\n", 2), tty_restore(tty), -1);
		if (input[0] != '\0')
			add_history(input);
		else
		{
			free(input);
			continue ;
		}
		tty_restore(tty);
		if (ft_correct_input(&input) == NULL)
		{
			data->exit_status = 2;
			continue ;
		}
		if (shell_loop_helper(input, data) != 0)
			return (-1);
	}
	return (tty_restore(tty), 0);
}
