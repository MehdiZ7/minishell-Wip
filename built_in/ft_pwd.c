/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:18:30 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/10 16:43:37 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_minishell *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		data->exit_status = 1;
		perror("pwd: ");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	data->exit_status = 0;
	return (0);
}
