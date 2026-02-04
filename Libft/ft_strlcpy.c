/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:34:19 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/13 13:22:41 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t lendest)
{
	size_t	i;

	if (!dest || !src)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i + 1 < lendest)
	{
		dest[i] = src[i];
		i++;
	}
	if (lendest > 0)
		dest[i] = '\0';
	return (ft_strlen(src));
}
