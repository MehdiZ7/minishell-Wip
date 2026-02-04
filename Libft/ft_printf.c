/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:03:33 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/27 16:49:39 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_format(va_list ap, char c, int *count)
{
	if (c == 'c')
		ft_putchar((char) va_arg(ap, int), count);
	else if (c == 's')
		ft_putstr(va_arg(ap, const char *), count);
	else if (c == 'i' || c == 'd')
		ft_putnbr(va_arg(ap, int), count);
	else if (c == 'u')
		ft_putunbr(va_arg(ap, unsigned int), count);
	else if (c == '%')
		ft_putchar('%', count);
	else if (c == 'x')
		ft_printhex(va_arg(ap, unsigned int), count);
	else if (c == 'X')
		ft_printmajhex(va_arg(ap, unsigned int), count);
	else if (c == 'p')
		ft_printadd((unsigned long)va_arg(ap, void *), count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	count = 0;
	va_start(ap, format);
	if (!format)
		return (-1);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_printf_format(ap, format[i], &count);
			i++;
			continue ;
		}
		ft_putchar(format[i], &count);
		i++;
	}
	return (count);
}
/*int	main(void)
{
	int		x;
	void	*ptr;

	x = 42 ;
	ptr = &x;

	ft_printf("ma fonction : %i \n", ft_printf("ma fonction : %c \n", 'c'));
	printf("la fonction : %i \n", printf("la fonction : %c \n", 'c'));

	ft_printf("ma fonction : %i \n",
	ft_printf("ma fonction : %s \n", "ceci est un test"));
	printf("la fonction : %i \n",
	printf("la fonction : %s \n", "ceci est un test"));

	ft_printf("ma fonction : %i \n", ft_printf("ma fonction : %p \n", ptr));
	printf("la fonction : %i \n",printf("la fonction : %p \n", ptr));

	ft_printf("ma fonction : %i \n", ft_printf("ma fonction : %d \n", 42));
	printf("la fonction : %i \n",printf("la fonction : %d \n", 42));

	ft_printf("ma fonction : %i \n", ft_printf("ma fonction : %i \n", 420));
	printf("la fonction : %i \n", printf("la fonction : %i \n", 420));

	ft_printf("ma fonction : %i \n",
		ft_printf("ma fonction : %u \n", 2147483647));
	printf("la fonction : %i \n", printf("la fonction : %u \n", 2147483647));

	ft_printf("ma fonction : %i \n", ft_printf("ma fonction : %x \n", 57480));
	printf("la fonction : %i \n", printf("la fonction : %x \n", 57480));

	ft_printf("ma fonction : %i \n", ft_printf("ma fonction : %X \n", 89670));
	printf("la fonction : %i \n", printf("la fonction : %X \n", 89670));

	ft_printf("ma fonction : %i \n", ft_printf("ma fonction : %% \n"));
	printf("la fonction : %i \n", printf("la fonction : %% \n"));

	return (0);
}*/
