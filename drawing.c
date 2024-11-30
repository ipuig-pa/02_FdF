/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:48:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/30 19:10:31 by ipuig-pa         ###   ########.fr       */
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

void	define_color(t_env *env)
{
	int	i;

	i = 0;
	env->min_z = env->coord[i].z;
	env->max_z = env->coord[i].z;
	if (env->def_color == 0)
	{
		while (i++ < (env->map_width * env->map_height))
		{
			if (env->coord[i - 1].z < env->min_z)
				env->min_z = env->coord[i - 1].z;
			else if (env->coord[i - 1].z > env->max_z)
				env->max_z = env->coord[i - 1].z;
		}
	}
	i = 0;
	while (i < (env->map_width * env->map_height))
	{
		if (env->max_z != env->min_z)
			env->fcoord[i].color = (env->coord[i].z - env->min_z) * \
						((RED - WHITE) / (env->max_z - env->min_z)) + WHITE;
		else
			env->fcoord[i].color = env->coord[i].color;
		i++;
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
	float	dc;
	int		steps;

	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	dc = point2.color - point1.color;
	steps = abs((int)dx) + 1;
	if (abs((int)dy) > abs((int)dx))
		steps = abs((int)dy) + 1;
	if (steps != 0)
	{
		dx = dx / steps;
		dy = dy / steps;
		dc = dc / steps;
	}
	while (steps >= 0)
	{
		my_pixel_put(env, (int)point1.x, (int)point1.y, (int)point1.color);
		point1.x = point1.x + dx;
		point1.y = point1.y + dy;
		point1.color = point1.color + dc;
		steps--;
	}
}

void	my_pixel_put(t_env *env, int x, int y, int color)
{
	int		offset;
	char	*pixel;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		finish_env(env, 1, "Points out of bounds\n");
	offset = (y * env->img.line_length + x * (env->img.bits_per_pixel / 8));
	pixel = env->img.addr + offset;
	*(unsigned int *)pixel = color;
}
