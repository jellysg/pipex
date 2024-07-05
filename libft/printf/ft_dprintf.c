/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:00:22 by jergoh            #+#    #+#             */
/*   Updated: 2024/06/08 22:00:23 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	checkformat_fd(const char *str, int i, va_list args, int fd)
{
	int	len;

	len = 0;
	if (str[i] == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (str[i] == 's')
		len += ft_putstr_fd(va_arg(args, char *), fd);
	else if (str[i] == 'p')
		len += ft_putaddress(va_arg(args, char *));
	else if (str[i] == 'd' || str[i] == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (str[i] == 'u')
		len += ft_putunbr(va_arg(args, int));
	else if (str[i] == 'x')
		len += ft_puthex_l(va_arg(args, unsigned int));
	else if (str[i] == 'X')
		len += ft_puthex_u(va_arg(args, unsigned int));
	else if (str[i] == '%')
		len += ft_putchar('%');
	return (i);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	int			i;
	int			length;
	va_list		args;

	i = 0;
	length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			length += checkformat_fd(str, i, args, fd);
		}
		else
			length += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(args);
	return (length);
}
