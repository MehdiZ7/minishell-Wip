/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:54:17 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/11 17:28:18 by mzouhir          ###   ########.fr       */
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

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	tmp_key = ft_substr(argv, 0, i);

	if (!is_key_ok(tmp_key))
		return (printf("export: '%s': not a valid identifier", tmp_key),
			free(tmp_key), 1);
	if (!argv[i])
		return (free(tmp_key), 0);
	tmp_value = ft_substr(argv, i + 1, ft_strlen(argv) - i - 1);
	if (update_env(tmp_key, tmp_value, data) != 0)
		return (free(tmp_key), free(tmp_value), 1);
	free(tmp_key);
	free(tmp_value);
	return (0);
}

int	ft_export(t_node *node, t_minishell *data)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!node->command.argv[1])
		return (0);
	while (node->command.argv[i])
	{
		if (export_the_arg(node->command.argv[i], data))
			ret = 1;
		i++;
	}
	data->exit_status = ret;
	return (ret);
}
