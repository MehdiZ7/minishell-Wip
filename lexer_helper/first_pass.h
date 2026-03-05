/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:54:48 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 18:59:22 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIRST_PASS_H
# define FIRST_PASS_H
# include "minishell.h"
# define STRS_CAP 1
# define NOT_IN_QUOTES 0
# define IN_SIMPLE_QUOTES 1
# define IN_DOUBLE_QUOTES 2

typedef struct s_replace_env
{
	ssize_t		*p_pos;
	size_t		*p_last_pos;
	int			*p_first;
	t_env		*env_head;
	t_env		**p_env;
	t_tab_str	**p_tab_strs;
	char		*str;
	int			exit_status;
	char		*temp_str;
}				t_replace_env;

ssize_t			ft_next_env_not_in_simple_quote(char *str, size_t pos);
void			ft_in_quotes(char *str, size_t pos, int *ret);
void			ft_remove_quotes(char *str);
size_t			ft_strlen_env(char *var);

void			ft_free_tab_str(t_tab_str **p_tab_str);
int				ft_grow_tab_str(t_tab_str *tab_str, float facteur);
int				ft_append_str_to_tab_str(t_tab_str **p_tab_strs, char *str);
int				ft_grow_last_str_of_tab_str(t_tab_str **p_tab_strs, char *str);
int				ft_replace_env(t_tab_str **p_tab_strs, char *str, t_env *env,
					int exit_status);
int				ft_not_special_str(t_tab_str **p_tab_strs, char *str);

t_tab_str		*ft_complete_string_treatment(t_env *env, t_tab_str *tmp,
					int exit_status);
t_tab_str		*ft_split_like_shell(char *str);
void			*append_helper(t_tab_str **p_tab, char *str, size_t start,
					size_t len);
int				is_split_operator(char c);
int				is_redir_or_heredoc(char *str, size_t i);
size_t			get_operator_end(char *str, size_t start);
#endif
