/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:54:17 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/23 12:52:49 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_key_ok(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_the_arg(char *argv, t_minishell *data)
{
	int		i;
	char	*tmp_key;
	char	*tmp_value;
	int		status;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	tmp_key = ft_substr(argv, 0, i);
	if (!is_key_ok(tmp_key))
		return (printf("export: '%s': not a valid identifier\n", tmp_key),
			free(tmp_key), 1);
	if (!argv[i])
		status = update_env(tmp_key, NULL, data);
	else
	{
		tmp_value = ft_substr(argv, i + 1, ft_strlen(argv) - i - 1);
		status = update_env(tmp_key, tmp_value, data);
		free(tmp_value);
	}
	free(tmp_key);
	if (!status)
		return (0);
	return (1);
}

void	print_tab(t_env *envp)
{
	t_env	*current;

	current = envp;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

void	sort_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;
	char	*tmp_key;
	char	*tmp_value;

	current = head;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strncmp(current->key, next->key
					, ft_strlen(current->key) + 1) > 0)
			{
				tmp_key = current->key;
				tmp_value = current->value;
				current->key = next->key;
				current->value = next->value;
				next->key = tmp_key;
				next->value = tmp_value;
			}
			next = next->next;
		}
		current = current->next;
	}
}

int	ft_export(t_node *node, t_minishell *data)
{
	int		i;
	int		ret;
	t_env	*envp;

	envp = NULL;
	i = 1;
	ret = 0;
	if (!node->command.argv[1])
	{
		envp = copy_env(data->env);
		sort_env_list(envp);
		print_tab(envp);
		free_env(envp);
		data->exit_status = 0;
		return (0);
	}
	while (node->command.argv[i])
	{
		if (export_the_arg(node->command.argv[i], data))
			ret = 1;
		i++;
	}
	data->exit_status = ret;
	return (ret);
}
