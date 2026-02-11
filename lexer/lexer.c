/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:01:10 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/08 22:09:25 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token *new, t_token **list)
{
	t_token	*tmp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*lexer(char *input)
{
	int		i;
	int		ret;
	t_token	*list;
	t_token	*tok;

	ret = 0;
	i = 0;
	list = NULL;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (ft_isseparator(input[i]))
			ret = handle_separator(input + i, &list);
		else if (input[i] == '\"' || input[i] == '\'')
			ret = handle_quotes(input + i, &list);
		else if (input[i] == '(')
		{
			tok = create_token("(", PAREN_OPEN);
			if (tok == NULL)
				ret = -1;
			else
			{
				token_add_back(tok, &list);
				ret = 1;
			}
		}
		else if (input[i] == ')')
		{
			tok = create_token(")", PAREN_CLOSE);
			if (tok == NULL)
				ret = -1;
			else
			{
				token_add_back(tok, &list);
				ret = 1;
			}
		}
		else
			ret = handle_cmd_or_arg(input + i, &list);
		if (ret < 0)
			return (free_token(list), NULL);
		i += ret;
	}
	return (list);
}
