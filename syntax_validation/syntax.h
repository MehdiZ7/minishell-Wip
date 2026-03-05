/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:21:46 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 14:27:58 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H
# include "minishell.h"

typedef struct s_checker
{
	char			*input;
	int				i;
	int				paren_balance;
	int				in_squote;
	int				in_dquote;
	t_token_type	last_token;
}					t_checker;

int					is_redir(t_token_type type);
const char			*get_token_str(t_token_type type);
void				ft_free_and_null(char **p_input, const char *error_msg);
int					is_operator(t_token_type type);
void				skip_spaces(t_checker *c);
#endif
