/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:04:10 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/26 17:11:48 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

void	ft_putchar(char c, int *count);
void	ft_putstr(const char *str, int *count);
void	ft_putnbr(int nb, int *count);
void	ft_putunbr(unsigned int nb, int *count);
void	ft_printhex(unsigned int nb, int *count);
void	ft_printmajhex(unsigned int nb, int *count);
void	ft_printadd(unsigned long nb, int *count);
void	ft_printf_format(va_list ap, char c, int *count);
int		ft_printf(const char *format, ...);

#endif
