/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 07:21:51 by lmilando          #+#    #+#             */
/*   Updated: 2026/03/02 09:55:43 by lmilando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ttyctx_init(t_ttyctx *ctx)
{
	ft_memset(ctx, 0, sizeof(t_ttyctx));
	ctx->is_tty = isatty(STDIN_FILENO);
	if (!ctx->is_tty)
		return (0);
	if (!ctx)
		return (-1);
	if (tcgetattr(STDIN_FILENO, &ctx->saved) == -1)
		return (-1);
	ctx->saved_ok = 1;
	return (0);
}

int	tty_disable_ctrl_backslash(const t_ttyctx *ctx)
{
	struct termios	t;

	if (!ctx || !ctx->saved_ok)
		return (-1);
	t = ctx->saved;
	t.c_cc[VQUIT] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
		return (-1);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void	tty_restore(const t_ttyctx *ctx)
{
	if (!ctx || !ctx->saved_ok)
		return ;
	tcsetattr(STDIN_FILENO, TCSANOW, &ctx->saved);
}
