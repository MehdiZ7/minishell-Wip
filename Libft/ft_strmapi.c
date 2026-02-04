/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:58:18 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/11 15:10:07 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	lendest;
	size_t	i;
	char	*mapi;

	if (!s || !f)
		return (NULL);
	lendest = ft_strlen(s);
	i = 0;
	mapi = malloc(sizeof(char) * (lendest + 1));
	if (mapi == NULL)
		return (NULL);
	while (s[i])
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}
