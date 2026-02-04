/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:19:35 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/11 15:09:51 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	lendest;
	size_t	lensrc;

	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	i = lendest;
	j = 0;
	if (siz == 0 || siz <= lendest)
		return (lensrc + siz);
	while (src[j] && siz > lendest + j + 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (lensrc + lendest);
}
