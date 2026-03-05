/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:04:24 by mzouhir           #+#    #+#             */
/*   Updated: 2026/03/04 14:20:20 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_env(t_env *src)
{
	t_env	*new_list;
	t_env	*node;

	new_list = NULL;
	while (src)
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (free_env(new_list), NULL);
		node->key = ft_strdup(src->key);
		if (src->value)
			node->value = ft_strdup(src->value);
		else
			node->value = NULL;
		node->next = NULL;
		env_add_back(node, &new_list);
		src = src->next;
	}
	return (new_list);
}

int	update_env(char *key, char *value, t_minishell *data)
{
	t_env	*envp;

	envp = data->env;
	while (envp)
	{
		if (!ft_strncmp(key, envp->key, ft_strlen(envp->key) + 1))
		{
			if (value)
			{
				free(envp->value);
				envp->value = ft_strdup(value);
				if (!envp->value)
					return (-1);
				return (0);
			}
			else
				return (0);
		}
		envp = envp->next;
	}
	if (create_new(key, value, data) != 0)
		return (-1);
	return (0);
}

int	create_new(char *key, char *value, t_minishell *data)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->next = NULL;
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (-1);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->key), free(new), -1);
	}
	else
		new->value = NULL;
	env_add_back(new, &data->env);
	return (0);
}

void	print_tab(t_env *envp)
{
	t_env	*current;

	current = envp;
	while (current)
	{
		ft_printf("declare -x %s", current->key);
		if (current->value)
			ft_printf("=\"%s\"", current->value);
		ft_printf("\n");
		current = current->next;
	}
}
