/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_not_special_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:56:19 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/22 10:56:21 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_pass.h"

int	ft_not_special_str(t_tab_str **p_tab_strs, char *str)
{
	if (ft_next_env_not_in_simple_quote(str, 0) != -1)
		return (0);
	if (ft_append_str_to_tab_str(p_tab_strs, str) == 0)
		return (-1);
	return (1);
}
