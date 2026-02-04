/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:10:15 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/13 16:03:00 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str, char c)
{
	int	flag;
	int	i;
	int	count;

	i = 0;
	flag = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && !flag)
		{
			count++;
			flag = 1;
		}
		else if (str[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

char	*malloc_word(const char *str, size_t start, size_t end)
{
	char	*malword;
	size_t	i;

	i = 0;
	malword = malloc(sizeof(char) * (end - start + 1));
	if (malword == NULL)
		return (NULL);
	while (start < end)
	{
		malword[i] = str[start];
		i++;
		start++;
	}
	malword[i] = '\0';
	return (malword);
}

void	freesplit(char **split, size_t words)
{
	while (words > 0)
		free(split[--words]);
	free(split);
}

int	fill_split(char **split, const char *s, char c)
{
	size_t	i;
	size_t	end;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		end = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			end++;
		}
		if (end != 0)
		{
			split[words] = malloc_word(s, i - end, i);
			if (!split[words])
				return (freesplit(split, words), -1);
			words++;
		}
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	size_t	words;

	words = count_words(s, c);
	split = malloc(sizeof(char *) * (words +1));
	if (!split)
		return (NULL);
	split[words] = NULL;
	if (fill_split(split, s, c) == -1)
		return (NULL);
	return (split);
}
