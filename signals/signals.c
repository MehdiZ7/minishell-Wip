/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:23:04 by lmilando          #+#    #+#             */
/*   Updated: 2026/02/18 16:46:16 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <curses.h>


int g_sig_val = 0;

static void	sig_int(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_val = 1;
}

void	signals_handler(void)
{
	g_sig_val = 0;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}
