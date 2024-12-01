/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:15:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/01 11:58:58 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_to_dec(char c)
{
	int	i;

	if (c >= '0' && c <= '9')
		i = c - '0';
	else if (c >= 'a' && c <= 'f')
		i = c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		i = c - 'A' + 10;
	else
		i = -1;
	return (i);
}

int	ft_atoi_hex(char *str)
{
	int	i;
	int	num;
	int	sign;
	int	c;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	c = hex_to_dec(str[i]);
	while (c >= 0)
	{
		num = 16 * num + c;
		i++;
		c = hex_to_dec(str[i]);
	}
	return (num * sign);
}
