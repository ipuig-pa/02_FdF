/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:21:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/04/11 18:55:44 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_final_coordinates(t_env *env)
{
	int		i;
	float	f;

	i = 0;
	f = 9.0 / 11;
	env->min_x = WINDOW_WIDTH;
	env->max_x = 0;
	env->min_y = WINDOW_HEIGHT;
	env->max_y = 0;
	while (i < (env->map_width * env->map_height))
	{
		env->fcoord[i].x = f * DISTX * env->coord[i].x * cos(M_PI / 6) \
						- (f * DISTY * env->coord[i].y * sin(M_PI / 3));
		env->fcoord[i].y = f * DISTY * env->coord[i].y * sin(M_PI / 6) + \
		(f * DISTX * env->coord[i].x * sin(M_PI / 6)) - f * env->coord[i].z;
		if (env->fcoord[i].x < env->min_x)
			env->min_x = env->fcoord[i].x;
		else if (env->fcoord[i].x > env->max_x)
			env->max_x = env->fcoord[i].x;
		if (env->fcoord[i].y < env->min_y)
			env->min_y = env->fcoord[i].y;
		else if (env->fcoord[i].y > env->max_y)
			env->max_y = env->fcoord[i].y;
		i++;
	}
}

void	fit_in_window(t_env *env)
{
	float		isize;
	float		fsize;
	float		scale;
	int			i;

	isize = (env->max_y - env->min_y);
	fsize = WINDOW_HEIGHT;
	if ((float)((env->max_x - env->min_x) / (env->max_y - env->min_y)) \
				> ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT))
	{
		isize = (env->max_x - env->min_x);
		fsize = WINDOW_WIDTH;
	}
	scale = (fsize - (2 * 0.01 * fsize)) / isize;
	i = 0;
	while (i < (env->map_width * env->map_height))
	{
		env->fcoord[i].x = ((env->fcoord[i].x - env->min_x) * scale) + \
			((WINDOW_WIDTH / 2) - ((env->max_x - env->min_x) / 2) * scale);
		env->fcoord[i].y = ((env->fcoord[i].y - env->min_y) * scale) + \
			((WINDOW_HEIGHT / 2) - ((env->max_y - env->min_y) / 2) * scale);
		i++;
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
	while (i++ < (env->map_width * env->map_height))
	{
		if (env->max_z != env->min_z)
			env->fcoord[i - 1].color = interpolate_color(WHITE, RED, \
			((float)(env->coord[i - 1].z - env->min_z) \
			/ (float)(env->max_z - env->min_z)));
		else
			env->fcoord[i - 1].color = env->coord[i - 1].color;
	}
}
