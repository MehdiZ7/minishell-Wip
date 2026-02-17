/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:32:23 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/16 14:58:34 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_wildcard(t_token *token)
{
	int		i;
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'' && in_double == false)
			in_single = !in_single;
		else if (token->value[i] == '"' && in_single == false)
			in_double = !in_double;
		if (token->value[i] == '*' && !in_single && !in_double)
		{
			token->type = WILDCARD;
			return (1);
		}
		i++;
	}
	return (0);
}

static bool	match_patern(char *file, char *pattern)
{
	if (*pattern == '*')
	{
		if (match_patern(file, pattern + 1))
			return (true);
		if (*file && match_patern(file + 1, pattern))
			return (true);
		return (false);
	}
	if (*file == *pattern)
	{
		if (!*pattern)
			return (true);
		return (match_patern(file + 1, pattern + 1));
	}
	return (false);
}

static int	replace_wildcard(t_token *token, t_token **tmp)
{
	char			*pattern;
	DIR				*directory;
	struct dirent	*entry;
	t_token			*new;

	pattern = remove_wildcard_quote(token->value);
	if (!pattern)
		return (-1);
	directory = opendir(".");
	if (!directory)
		return (free(pattern), -1);
	entry = readdir(directory);
	while (entry)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(directory);
			continue ;
		}
		if (match_patern(entry->d_name, pattern))
		{
			new = create_token(entry->d_name, CMD_OR_ARG);
			if (!new)
				return (free(pattern), -2);
			token_add_back(new, tmp);
		}
		entry = readdir(directory);
	}
	free(pattern);
	return (closedir(directory), 0);
}

void	sort_list(t_token *list)
{
	t_token	*head;
	t_token	*current;
	char	*tmp;
	int		len;

	head = list;
	if (!list || !list->next)
		return ;
	while (head)
	{
		current = head->next;
		while (current)
		{
			len = ft_strlen(head->value);
			if ((int)ft_strlen(current->value) > len)
				len = ft_strlen(current->value);
			if (ft_strncmp(current->value, head->value, len + 1) < 0)
			{
				tmp = current->value;
				current->value = head->value;
				head->value = tmp;
			}
			current = current->next;
		}
		head = head->next;
	}
}

int	expand_wildcard(t_minishell *data)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next_token;
	t_token	*tmp;
	t_token	*tmp_end;

	prev = NULL;
	current = data->tokens;
	while (current)
	{
		tmp = NULL;
		if (check_for_wildcard(current))
		{
			if (replace_wildcard(current, &tmp) < 0)
			{
				if (tmp)
					free_token(tmp);
				return (1);
			}
			sort_list(tmp);
			if (!tmp)
				current->type = CMD_OR_ARG;
			else
			{
				next_token = current->next;
				if (!prev)
					data->tokens = tmp;
				else
					prev->next = tmp;
				tmp_end = tmp;
				while (tmp_end->next)
					tmp_end = tmp_end->next;
				tmp_end->next = next_token;
				free(current->value);
				free(current);
				prev = tmp_end;
				current = next_token;
				continue ;
			}
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
