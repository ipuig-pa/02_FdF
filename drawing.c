/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:48:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/28 17:33:32 by ipuig-pa         ###   ########.fr       */
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
		//ft_printf("prei: %i\n", i);
		if ((i + 1) % env->map_width != 0)
		{
			printf("pre-nexti: %i; x:%f, y: %f, x2: %f, Y2: %f\n", i, env->fcoord[i].x, env->fcoord[i].y, env->fcoord[i + 1].x, env->fcoord[i + 1].y);
			join_points(env, env->fcoord[i].x, env->fcoord[i].y, env->fcoord[i + 1].x, env->fcoord[i + 1].y);
			ft_printf("post-nexti: %i\n", i);
		}
		if (i < ((env->map_height - 1) * env->map_width))
		{
			ft_printf("pre-downi: %i\n", i);
			join_points(env, env->fcoord[i].x, env->fcoord[i].y, env->fcoord[i + env->map_width].x, env->fcoord[i + env->map_width].y);
			ft_printf("post-downi: %i\n", i);
		}
		//ft_printf("posti: %i\n", i);
		i++;
	}
	//tenir en compte el color
	//my_pixel_put(env->img, x, y, 0x00FF0000);//is going to print a red pixel. Need to create a while loop for all the pixels in our 2D array of 2D that should be printed. 
}

void	join_points(t_env *env, float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;
	int		steps;
	int		i;

	//ft_printf("check\n");
	dx = x2 - x1;
	dy = y2 - y1;
	//printf("dx: %lf, dy: %lf\n", dx, dy);
	steps = abs((int)dx);
	if (dy > dx)
		steps = abs((int)dy);
	//ft_printf("steps: %i\n", steps);
	dx = dx / steps;
	dy = dy / steps;
	i = 0;
	while (i < steps)
	{
		//ft_printf("put; x1: %i, y1: %i\n", (int)x1, (int)y1);
		my_pixel_put(&(env->img), (int)x1, (int)y1, WHITE);
		x1 = x1 + dx;
		y1 = y1 + dy;
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



