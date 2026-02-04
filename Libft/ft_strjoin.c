/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:36:37 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/11 15:09:47 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	prelen;
	size_t	suflen;
	char	*joined;

	prelen = ft_strlen(s1);
	suflen = ft_strlen(s2);
	joined = malloc(sizeof(char) * (prelen + suflen + 1));
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, prelen + 1);
	ft_strlcat(joined, s2, suflen + prelen + 1);
	return (joined);
}
