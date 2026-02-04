/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:56:38 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/20 12:21:05 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nb, int *count)
{
	if (nb == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-', count);
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10, count);
	ft_putchar(nb % 10 + '0', count);
}
