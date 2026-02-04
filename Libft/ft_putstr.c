/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:53:53 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/26 17:03:37 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(const char *str, int *count)
{
	int	i;

	if (!str)
		return (ft_putstr("(null)", count));
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], count);
		i++;
	}
}
