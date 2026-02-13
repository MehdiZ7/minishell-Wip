/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:54:17 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/13 11:43:41 by mzouhir          ###   ########.fr       */
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

void	print_tab(char **envp)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
	while (envp[i])
	{
		flag = false;
		j = 0;
		printf("declare -x ");
		while (envp[i][j])
		{
			printf("%c", envp[i][j]);
			if (envp[i][j] == '=' && !flag)
			{
				printf("\"");
				flag = true;
			}
			j++;
		}
		if (flag == true)
			printf("\"");
		printf("\n");
		i++;
	}
}

void	sort_tab(char **envp)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	if (!envp)
		return ;
	while (envp[i] && envp[i + 1])
	{
		len = ft_strlen(envp[i]);
		if ((int)ft_strlen(envp[i + 1]) > len)
			len = ft_strlen(envp[i + 1]);
		if (ft_strncmp(envp[i], envp[i + 1], len + 1) > 0)
		{
			tmp = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	print_tab(envp);
	free_args(envp);
}


int	ft_export(t_node *node, t_minishell *data)
{
	int		i;
	int		ret;
	char	**envp;

	envp = NULL;
	i = 1;
	ret = 0;
	if (!node->command.argv[1])
	{
		if (data->env)
			envp = list_to_tab(data->env);
		sort_tab(envp);
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
