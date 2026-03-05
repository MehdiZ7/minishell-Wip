/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:43:00 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 14:36:51 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static void	skip_word(t_checker *c)
{
	while (c->input[c->i])
	{
		if (c->input[c->i] == '\'' && !c->in_dquote)
		{
			c->in_squote = !c->in_squote;
			c->i++;
		}
		else if (c->input[c->i] == '"' && !c->in_squote)
		{
			c->in_dquote = !c->in_dquote;
			c->i++;
		}
		else if (c->in_squote || c->in_dquote)
			c->i++;
		else if (c->input[c->i] == ' ' || c->input[c->i] == '\t'
			|| c->input[c->i] == '\n' || c->input[c->i] == '|'
			|| c->input[c->i] == '&' || c->input[c->i] == '>'
			|| c->input[c->i] == '<' || c->input[c->i] == '('
			|| c->input[c->i] == ')')
			break ;
		else
			c->i++;
	}
}

static t_token_type	get_next_token(t_checker *c)
{
	skip_spaces(c);
	if (!c->input[c->i])
		return (UNRECOGNIZED);
	if (c->input[c->i] == '|' && c->input[c->i + 1] == '|')
		return (c->i += 2, OR);
	if (c->input[c->i] == '&' && c->input[c->i + 1] == '&')
		return (c->i += 2, AND);
	if (c->input[c->i] == '|')
		return (c->i++, PIPE);
	if (c->input[c->i] == '>' && c->input[c->i + 1] == '>')
		return (c->i += 2, APPEND);
	if (c->input[c->i] == '<' && c->input[c->i + 1] == '<')
		return (c->i += 2, HEREDOC);
	if (c->input[c->i] == '>')
		return (c->i++, REDIR_OUT);
	if (c->input[c->i] == '<')
		return (c->i++, REDIR_IN);
	if (c->input[c->i] == '(')
		return (c->i++, PAREN_OPEN);
	if (c->input[c->i] == ')')
		return (c->i++, PAREN_CLOSE);
	return (CMD_OR_ARG);
}

static int	validate_token(t_checker *c, t_token_type token)
{
	if (is_operator(token))
	{
		if (c->last_token == UNRECOGNIZED || c->last_token == PAREN_OPEN
			|| is_operator(c->last_token))
			return (0);
	}
	if (is_redir(c->last_token) && token != CMD_OR_ARG)
		return (0);
	if (c->last_token == PAREN_OPEN && token == PAREN_CLOSE)
		return (0);
	if (token == PAREN_CLOSE)
	{
		c->paren_balance--;
		if (c->paren_balance < 0)
			return (0);
		if (is_operator(c->last_token))
			return (0);
	}
	return (1);
}

void	ft_init_checker(t_checker *c, char **p_input)
{
	ft_memset(c, 0, sizeof(t_checker));
	(*c).input = *p_input;
	(*c).last_token = UNRECOGNIZED;
}

char	*ft_correct_input(char **p_input)
{
	t_checker		c;
	t_token_type	token;

	ft_init_checker(&c, p_input);
	while (1)
	{
		token = get_next_token(&c);
		if (token == UNRECOGNIZED)
			break ;
		if (!validate_token(&c, token))
			return (ft_free_and_null(p_input, get_token_str(token)), NULL);
		if (token == PAREN_OPEN)
			c.paren_balance++;
		if (token == CMD_OR_ARG)
			skip_word(&c);
		c.last_token = token;
	}
	if (is_operator(c.last_token))
		return (ft_free_and_null(p_input, "newline"), NULL);
	if (is_redir(c.last_token))
		return (ft_free_and_null(p_input, "newline"), NULL);
	if (c.paren_balance != 0)
		return (ft_free_and_null(p_input, "newline"), NULL);
	return (*p_input);
}
