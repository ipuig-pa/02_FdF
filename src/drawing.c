/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:48:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/04/11 18:38:46 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	paint_background(t_env *env, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			my_pixel_put(env, x, y, color);
			y++;
		}
		x++;
	}
}

void	put_line(t_env *env)
{
	int	i;

	i = 0;
	while (i < (env->map_height * env->map_width))
	{
		if ((i + 1) % env->map_width != 0)
			join_points(env, env->fcoord[i], env->fcoord[i + 1]);
		if (i < ((env->map_height - 1) * env->map_width))
			join_points(env, env->fcoord[i], env->fcoord[i + env->map_width]);
		i++;
	}
}

void	join_points(t_env *env, t_fcoord point1, t_fcoord point2)
{
	float	dx;
	float	dy;
	float	dt;
	float	t;
	int		steps;

	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	steps = abs((int)dx) + 1;
	if (abs((int)dy) > abs((int)dx))
		steps = abs((int)dy) + 1;
	dx = dx / steps;
	dy = dy / steps;
	dt = 1.0 / steps;
	t = 0.0;
	while (steps >= 0)
	{
		my_pixel_put(env, (int)point1.x, (int)point1.y, \
					interpolate_color(point1.color, point2.color, t));
		point1.x = point1.x + dx;
		point1.y = point1.y + dy;
		t = t + dt;
		steps--;
	}
}

int	interpolate_color(int col1, int col2, float t)
{
	int	r;
	int	g;
	int	b;

	if (col1 == col2 || t == 0)
		return (col1);
	r = ((col1 >> 16) & 0xFF) + \
		t * (((col2 >> 16) & 0xFF) - ((col1 >> 16) & 0xFF));
	g = ((col1 >> 8) & 0xFF) + \
		t * (((col2 >> 8) & 0xFF) - ((col1 >> 8) & 0xFF));
	b = (col1 & 0xFF) + t * ((col2 & 0xFF) - (col1 & 0xFF));
	return ((r << 16) | (g << 8) | b);
}

void	my_pixel_put(t_env *env, int x, int y, int color)
{
	int		offset;
	char	*pixel;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		finish_env(env, 1, "Points out of bounds");
	offset = (y * env->img.line_length + x * (env->img.bits_per_pixel / 8));
	pixel = env->img.addr + offset;
	*(unsigned int *)pixel = color;
}
