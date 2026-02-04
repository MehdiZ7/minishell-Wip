/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:30:30 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/20 12:15:04 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printall(unsigned long nb, int *count)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb > 15)
		ft_printall(nb / 16, count);
	ft_putchar(base[nb % 16], count);
}

void	ft_printadd(unsigned long nb, int *count)
{
	if (nb == 0)
	{
		ft_putstr("(nil)", count);
		return ;
	}
	ft_putstr("0x", count);
	ft_printall(nb, count);
}
