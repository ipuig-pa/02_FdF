/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:03:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:16:53 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	else
		return (write(1, s, ft_strlen(s)));
}

int	ft_putptr(void *p)
{
	int			prefix_print;
	int			address_print;
	uintptr_t	ptr;

	if (!p)
		return (ft_putstr("0x0"));
	ptr = (uintptr_t)p;
	prefix_print = ft_putstr("0x");
	if (prefix_print == -1)
		return (-1);
	address_print = ft_putun_base(ptr, "0123456789abcdef");
	if (address_print == -1)
		return (-1);
	return (prefix_print + address_print);
}

int	ft_putnbr(int n)
{
	long	n_c;
	int		printed_char;
	int		printed_temp;

	n_c = n;
	printed_char = 0;
	if (n < 0)
	{
		printed_temp = write(1, "-", 1);
		if (printed_temp == -1)
			return (-1);
		n_c = -n_c;
		printed_char = printed_temp;
	}
	if (n_c >= 10)
	{
		printed_temp = ft_putnbr(n_c / 10);
		if (printed_temp == -1)
			return (-1);
		printed_char = printed_char + printed_temp;
	}
	printed_temp = ft_putchar('0' + n_c % 10);
	if (printed_temp == -1)
		return (-1);
	return (printed_char + printed_temp);
}
