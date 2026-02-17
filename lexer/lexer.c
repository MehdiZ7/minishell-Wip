/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:01:10 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/15 15:24:22 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_lexer_helper
{
	t_token	**p_tok;
	t_token	**p_list;
}			t_lexer_helper;

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

static void	lexer_helper(char *input, int i, int *p_ret, t_lexer_helper a)
{
	if (input[i] == '(')
	{
		*(a.p_tok) = create_token("(", PAREN_OPEN);
		if (*(a.p_tok) == NULL)
			*p_ret = -1;
		else
		{
			token_add_back(*(a.p_tok), a.p_list);
			*p_ret = 1;
		}
	}
	else if (input[i] == ')')
	{
		*(a.p_tok) = create_token(")", PAREN_CLOSE);
		if (*(a.p_tok) == NULL)
			*p_ret = -1;
		else
		{
			token_add_back(*(a.p_tok), a.p_list);
			*p_ret = 1;
		}
	}
	else
		*p_ret = handle_cmd_or_arg(input + i, a.p_list);
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
		else
			lexer_helper(input, i, &ret, (t_lexer_helper){&tok, &list});
		if (ret < 0)
			return (free_token(list), NULL);
		i += ret;
	}
	return (list);
}
