/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:15:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/01 11:58:55 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_base(char *base, int n)
{
	int	actual_pos;
	int	other_previous_pos;

	if (!base)
		return (0);
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

static int	is_contained_where(char to_find, char *base)
{
	int	w;

	w = 0;
	while (base[w] != 0)
	{
		if (base[w] == to_find)
			return (w);
		w++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	num;
	int	sign;
	int	n_base;

	n_base = ft_strlen(base);
	if (!is_valid_base(base, n_base))
		return (0);
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
	while (is_contained_where(str[i], base) >= 0)
	{
		num = n_base * num + is_contained_where(str[i], base);
		i++;
	}
	return (num * sign);
}
