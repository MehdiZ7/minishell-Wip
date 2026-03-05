/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:10:19 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/28 13:16:10 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_PARSING_H
# define AST_PARSING_H
# include "minishell.h"

void	cleanup_ast_on_error(t_list **pile, t_list **postfix);
t_node	*pop_stack(t_list **stack);
void	*create_ast_loop(t_list **p_pile, t_list **p_postfix, t_node **p_cur);
#endif
