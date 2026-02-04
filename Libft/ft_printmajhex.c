/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmajhex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:11:27 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/20 12:12:37 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printmajhex(unsigned int nb, int *count)
{
	char			*base;

	base = "0123456789ABCDEF";
	if (nb > 15)
		ft_printmajhex(nb / 16, count);
	ft_putchar(base[nb % 16], count);
}
