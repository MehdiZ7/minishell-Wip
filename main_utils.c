/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:32:42 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/05 15:03:59 by mzouhir          ###   ########.fr       */
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
		data->tokens = lexer(input);
		if (!data->tokens)
			return (free(input), -1);
		if (get_expansion(data) == -1)
			return (free(input), -1);
		print_list(data->tokens);
		free(input);
		free_token(data->tokens);
		data->tokens = NULL;
	}
	return (0);
}
