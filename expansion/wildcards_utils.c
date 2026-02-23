/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:29:26 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/17 14:15:32 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len(char *head, char *current)
{
	int	len;

	len = ft_strlen(head);
	if ((int)ft_strlen(current) > len)
		len = ft_strlen(current);
	return (len);
}

int	check_entry(struct dirent *entry, t_token **tmp, char *pat)
{
	t_token	*new;

	if (entry->d_name[0] == '.' && pat[0] != '.')
		return (0);
	if (match_patern(entry->d_name, pat))
	{
		new = create_token(entry->d_name, CMD_OR_ARG);
		if (!new)
			return (-2);
		token_add_back(new, tmp);
	}
	return (0);
}

t_token	*insert_wildcards(t_token **head,
	t_token *tmp, t_token *prev, t_token *cur)
{
	t_token	*last;

	if (!prev)
		*head = tmp;
	prev->next = tmp;
	last = tmp;
	while (last->next)
		last = last->next;
	last->next = cur->next;
	free(cur->value);
	free(cur);
	return (last);
}

t_token	*init_wildcards(t_token **prev, t_token *head)
{
	*prev = NULL;
	return (head);
}
