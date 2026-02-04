/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:11:59 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/03 18:34:54 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*list;
	t_env	*env;

	list = NULL;
	env = init_env(envp);
	if (!env)
		return (1);
	(void)ac;
	(void)av;
	(void)env;
	//print_env(env);
	while (1)
	{
		input = readline("minishell>$ ");
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		list = lexer(input);
		print_list(list);
		free(input);
	}
	return (0);
	free_env(env);

}
