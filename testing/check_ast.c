/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:11:05 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/06 14:44:00 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ast_all(void)
{
	t_node			*test;
	char			**args;
	t_redir_node	*redir;
	int				i;

	i = 0;
	test = create_ast_node(NODE_CMD);
	args = malloc(sizeof(char *) * 3);
	while (i < 3)
	{
		ft_strdup("test");
		i++;
	}
	redir = malloc(sizeof(t_redir_node));
	ft_strlcpy(redir->filename, "redir", 6);
	redir->type = REDIR_IN_FILE;
	free_ast_node(test);
	return (0);
}
