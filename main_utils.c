/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:32:42 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/12 11:04:15 by lmilando         ###   ########.fr       */
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

static int	shell_loop_helper(char *input, t_minishell *data)
{
	if (get_expansion(data) == -1)
		return (free(input), -1);
	if (remove_quote(data) == -1)
		return (free(input), -1);
	free(input);
	data->ast = create_ast(data);
	free_token(data->tokens);
	data->tokens = NULL;
	print_ast(data->ast, 0);
	executor(data->ast, data);
	free_ast_node(data->ast);
	data->tokens = NULL;
	return (0);
}

int	shell_loop(t_minishell *data)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("minishell>$ ");
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		else
		{
			free(input);
			continue ;
		}
		data->tokens = lexer(input);
		if (!data->tokens)
		{
			free(input);
			continue ;
		}
		if (shell_loop_helper(input, data) != 0)
			return (-1);
	}
	return (0);
}
