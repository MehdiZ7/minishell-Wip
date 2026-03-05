/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:25:56 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 14:30:46 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	is_operator(t_token_type type)
{
	return (type == PIPE || type == AND || type == OR);
}

int	is_redir(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == APPEND
		|| type == HEREDOC);
}

const char	*get_token_str(t_token_type type)
{
	if (type == PIPE)
		return ("|");
	if (type == AND)
		return ("&&");
	if (type == OR)
		return ("||");
	if (type == PAREN_CLOSE)
		return (")");
	if (type == UNRECOGNIZED)
		return ("newline");
	return ("operator");
}

void	ft_free_and_null(char **p_input, const char *error_msg)
{
	if (error_msg)
		fprintf(stderr, "syntax error near unexpected token `%s'\n", error_msg);
	free(*p_input);
	*p_input = NULL;
}

void	skip_spaces(t_checker *c)
{
	while (c->input[c->i] && (c->input[c->i] == ' ' || c->input[c->i] == '\t'
			|| c->input[c->i] == '\n'))
		c->i++;
}
