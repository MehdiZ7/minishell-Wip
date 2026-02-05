/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:09:38 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/05 14:51:14 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_value(char *key, t_minishell *data)
{
	t_env	*envp;

	envp = data->env;
	if (key[0] == '?' && key[1] == '\0')
		return (ft_itoa(data->exit_status));
	while (envp)
	{
		if (ft_strlen(key) == ft_strlen(envp->key)
			&& !ft_strncmp(key, envp->key, ft_strlen(envp->key)))
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (ft_strdup(""));
}

static char	*create_new_value(char *old, char *val, int index, int len)
{
	char	*new;
	int		old_size;
	int		new_size;

	old_size = ft_strlen(old);
	new_size = old_size - len - 1 + ft_strlen(val);
	new = malloc(sizeof(char) * (new_size + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, old, index + 1);
	ft_strlcat(new, val, new_size + 1);
	ft_strlcat(new, old + (index + len + 1), new_size + 1);
	return (new);
}

int	replace_var(t_token *token, char *key, int index, t_minishell *data)
{
	char	*val;
	char	*new_var;

	val = get_var_value(key, data);
	if (!val)
		return (-1);
	new_var = (create_new_value(token->value, val, index, ft_strlen(key)));
	if (!new_var)
	{
		free(val);
		return (-1);
	}
	free(token->value);
	token->value = new_var;
	free(val);
	if (!token->value)
		return (-1);
	return (1);
}


