/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:20:27 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/05 16:17:53 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token *list)
{
	while (list)
	{
		printf("type: %d  value :%s\n", list->type, list->value);
		list = list->next;
	}
}

void	print_env(t_env	*list)
{
	while (list)
	{
		printf("key : %s\nvalue: %s\n", list->key, list->value);
		list = list->next;
	}
}
