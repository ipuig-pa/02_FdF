/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putun_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:06:37 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:16:50 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putun_base_n(uintptr_t nb, int n, char *base)
{
	char	arr[32];
	int		j;
	int		printed_char;
	int		printed_temp;

	j = 0;
	printed_char = 0;
	if (nb == 0)
		return (write(1, &base[0], 1));
	while (nb != 0)
	{
		arr[j] = base[nb % n];
		nb = nb / n;
		j++;
	}
	j--;
	while (j >= 0)
	{
		printed_temp = write(1, &arr[j], 1);
		if (printed_temp == -1)
			return (-1);
		printed_char = printed_char + printed_temp;
		j--;
	}
	return (printed_char);
}

static int	is_valid_base(char *base, int n)
{
	int	actual_pos;
	int	other_previous_pos;

	actual_pos = 0;
	if (n <= 1)
		return (0);
	while (actual_pos < n)
	{
		if (base[actual_pos] == '-' || base[actual_pos] == '+')
			return (0);
		other_previous_pos = 0;
		while (other_previous_pos < actual_pos)
		{
			if (base[actual_pos] == base[other_previous_pos])
				return (0);
			other_previous_pos++;
		}
		actual_pos++;
	}
	return (1);
}

int	ft_putun_base(uintptr_t nbr, char *base)
{
	int	n;

	n = 0;
	if (!base)
		return (-1);
	while (base[n] != '\0')
		n++;
	if (is_valid_base(base, n))
		return (ft_putun_base_n(nbr, n, base));
	return (-1);
}
