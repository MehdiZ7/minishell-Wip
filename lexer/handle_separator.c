/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:27:51 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/15 14:10:53 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int		handle_separator_vertical_bar(char *input, t_token **list);
int		handle_separator_comp_sign(char *input, t_token **list);
int		handle_separator_comp_sign2(char *input, t_token **list);

int	error_handling(char *input, size_t start, char *grp)
{
	if (ft_first_char_not_ingroup(input, start, " \t\f\v") == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline\'\n",
			STDERR_FILENO);
		return (-1);
	}
	if (ft_strchr(grp, ft_first_char_not_ingroup(input, start, " \t\f\v")))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putchar_fd(ft_first_char_not_ingroup(input, 2, " \t\f\v"),
			STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	extract_sep(t_token **list, char *value, t_token_type type, int len)
{
	t_token	*new;

	new = create_token(value, type);
	if (!new)
		return (-1);
	token_add_back(new, list);
	return (len);
}

char	*ft_extract_str(char *input, int *p_len)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	len = 0;
	while (input[i + len] != 0 && !ft_isspace(input[i + len]))
		len++;
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &input[i], len + 1);
	*p_len = i + len;
	return (str);
}

int	handle_separator(char *input, t_token **list)
{
	int	ret;

	ret = handle_separator_vertical_bar(input, list);
	if (ret != INT_MAX)
		return (ret);
	ret = handle_separator_comp_sign(input, list);
	if (ret != INT_MAX)
		return (ret);
	ret = handle_separator_comp_sign2(input, list);
	if (ret != INT_MAX)
		return (ret);
	return (0);
}
