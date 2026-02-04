/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:29:55 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/12 17:34:39 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_malloc_size(long nbr)
{
	size_t	size;

	size = 0;
	if (nbr < 0)
	{
		size++;
		nbr *= -1;
	}
	while (nbr > 9)
	{
		size++;
		nbr /= 10;
	}
	size++;
	return (size);
}

char	*ft_itoa(int nbr)
{
	size_t	size;
	long	nb;
	char	*result;
	size_t	is_negative;

	size = ft_malloc_size((long)(nbr));
	result = malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	nb = (long)(nbr);
	is_negative = 0;
	if (nb < 0)
	{
		result[0] = '-';
		nb *= -1;
		is_negative = 1;
	}
	while (size > is_negative)
	{
		result[size - 1] = nb % 10 + '0';
		nb /= 10;
		size--;
	}
	return (result);
}
