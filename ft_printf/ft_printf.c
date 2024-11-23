/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:48:12 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:00:15 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_arg(char specifier, va_list args)
{
	int	printed_char;

	printed_char = -1;
	if (specifier == 'c')
		printed_char = ft_putchar((char)va_arg (args, int));
	else if (specifier == 's')
		printed_char = ft_putstr(va_arg (args, char *));
	else if (specifier == 'p')
		printed_char = ft_putptr(va_arg (args, void *));
	else if (specifier == 'd' || specifier == 'i')
		printed_char = ft_putnbr(va_arg (args, int));
	else if (specifier == 'u')
		printed_char = ft_putun_base((uintptr_t) \
	va_arg (args, unsigned int), "0123456789");
	else if (specifier == 'x')
		printed_char = ft_putun_base((uintptr_t) \
	va_arg (args, unsigned int), "0123456789abcdef");
	else if (specifier == 'X')
		printed_char = ft_putun_base((uintptr_t) \
	va_arg (args, unsigned int), "0123456789ABCDEF");
	else if (specifier == '%')
		printed_char = ft_putchar('%');
	return (printed_char);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		printed_char;
	int		total_printed;

	va_start(args, format);
	i = -1;
	total_printed = 0;
	if (!format)
		return (-1);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			printed_char = write_arg(format[i], args);
		}
		else
			printed_char = ft_putchar(format[i]);
		if (printed_char == -1)
			return (-1);
		total_printed = total_printed + printed_char;
	}
	va_end (args);
	return (total_printed);
}
