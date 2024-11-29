/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:48:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/29 15:57:30 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_env(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		return (0);
	env->mlx_window = mlx_new_window(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, env->map_file);
	/*if(!env->mlx_window)
	{
		//handle error
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		return (0);
	}*/
	env->img.img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	/*if(!env->img.img)
	{
		//handle error
		mlx_destroy_window(mlx_window);
		mlx_destroy_display(mlx);
		free(mlx);
		return (0);
	}*/
	env->img.addr = mlx_get_data_addr(env->img.img, &(env->img.bits_per_pixel), &(env->img.line_length), &(env->img.endian));
	paint_background(env, BLACK);
	return (1);
}

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
			my_pixel_put(&(env->img), x, y, color);
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
		ft_printf("i: %i, color: %X\n", i, env->fcoord[i].color);
		if ((i + 1) % env->map_width != 0)
		{
			printf("pre-nexti: %i; x:%f, y: %f, x2: %f, Y2: %f\n", i, env->fcoord[i].x, env->fcoord[i].y, env->fcoord[i + 1].x, env->fcoord[i + 1].y);
			join_points(env, env->fcoord[i], env->fcoord[i + 1]);
			ft_printf("post-nexti: %i\n", i);
		}
		if (i < ((env->map_height - 1) * env->map_width))
		{
			ft_printf("pre-downi: %i\n", i);
			join_points(env, env->fcoord[i], env->fcoord[i + env->map_width]);
			ft_printf("post-downi: %i\n", i);
		}
		ft_printf("posti: %i\n", i);
		i++;
	}
}

void	join_points(t_env *env, t_fcoord point1, t_fcoord point2)
{
	float	dx;
	float	dy;
	int		dc;
	int		steps;
	int		i;

	ft_printf("check\n");
	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	dc = point2.color - point1.color;
	printf("dx: %lf, dy: %lf\n", dx, dy);
	steps = abs((int)dx);
	if (dy > dx)
		steps = abs((int)dy);
	ft_printf("steps: %i\n", steps);
	if (steps != 0)
	{
		dx = dx / steps;
		dy = dy / steps;
		dc = dc / steps;
	}
	i = 0;
	while (i <= steps)
	{
		//ft_printf("put; x1: %i, y1: %i\n", (int)x1, (int)y1);
		my_pixel_put(&(env->img), (int)point1.x, (int)point1.y, point1.color);
		point1.x = point1.x + dx;
		point1.y = point1.y + dy;
		point1.color = point1.color + dc;
		i++;
	}
}
void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int		offset;
	char	*pixel;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	pixel = img->addr + offset;
	*(unsigned int*)pixel = color;
}



