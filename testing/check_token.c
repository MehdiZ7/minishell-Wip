/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:20:27 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/11 19:05:22 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_token_type_helper(t_token_type tok)
{
	if (tok == UNRECOGNIZED)
		ft_putstr_fd("UNRECOGNIZED", STDOUT_FILENO);
	else if (tok == SINGLE_QUOTE)
		ft_putstr_fd("SINGLE_QUOTE", STDOUT_FILENO);
	else if (tok == DOUBLE_QUOTE)
		ft_putstr_fd("DOUBLE_QUOTE", STDOUT_FILENO);
	else if (tok == PIPE)
		ft_putstr_fd("PIPE", STDOUT_FILENO);
	else if (tok == REDIR_IN)
		ft_putstr_fd("REDIR_IN", STDOUT_FILENO);
	else if (tok == REDIR_OUT)
		ft_putstr_fd("REDIR_OUT", STDOUT_FILENO);
	else if (tok == HEREDOC)
		ft_putstr_fd("HEREDOC", STDOUT_FILENO);
	else if (tok == APPEND)
		ft_putstr_fd("APPEND", STDOUT_FILENO);
	else if (tok == AND)
		ft_putstr_fd("AND", STDOUT_FILENO);
	else
		return (0);
	return (1);
}

static void	print_token_type(t_token_type tok)
{
	if (print_token_type_helper(tok))
		;
	else if (tok == OR)
		ft_putstr_fd("OR", STDOUT_FILENO);
	else if (tok == PAREN_OPEN)
		ft_putstr_fd("PAREN_OPEN", STDOUT_FILENO);
	else if (tok == PAREN_CLOSE)
		ft_putstr_fd("PAREN_CLOSE", STDOUT_FILENO);
	else if (tok == WILDCARD)
		ft_putstr_fd("WILDCARD", STDOUT_FILENO);
	else if (tok == CMD_OR_ARG)
		ft_putstr_fd("CMD_OR_ARG", STDOUT_FILENO);
	else if (tok == ENV)
		ft_putstr_fd("ENV", STDOUT_FILENO);
	else
	{
		ft_putstr_fd("UNREACHABLE", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	print_list(t_token *list)
{
	while (list)
	{
		ft_putstr_fd("type : ", STDOUT_FILENO);
		print_token_type(list->type);
		ft_printf(" value :%s\n", list->value);
		list = list->next;
	}
}

void	print_env(t_env *list)
{
	while (list)
	{
		ft_printf("key : %s\nvalue: %s\n", list->key, list->value);
		list = list->next;
	}
}
