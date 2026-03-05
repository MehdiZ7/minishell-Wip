/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:23:04 by lmilando          #+#    #+#             */
/*   Updated: 2026/03/04 12:35:08 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>

int						g_sig_val = 0;

static void	sig_int(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_val = 130;
}

void	sig_int_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "^C", 2);
	g_sig_val = 130;
	close(STDIN_FILENO);
}

void	signals_handler(void)
{
	g_sig_val = 0;
	signal(SIGINT, sig_int);
}
