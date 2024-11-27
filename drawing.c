/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:48:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/27 17:08:46 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_env(t_env *env)
{
	env->mlx = mlx_init();
	if (!mlx)
		return (1);
	env->mlx_window = mlx_new_window(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, env->map_file);
	if(!env->mlx_window)
	{
		//handle error
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		return (1);
	}
	env->img.img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if(!env->img.img)
	{
		//handle error
		mlx_destroy_window(mlx_window);
		mlx_destroy_display(mlx);
		free(mlx);
		return (1);
	}
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel, &env->img.line_length, &img.endian);
	paint_background(env, BLACK);
	return (0);
}

void	paint_background(t_env *env, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WINDOW_WIDTH)
	{
		while (y < WINDOW_HEIGHT)
		{
			my_pixel_put(env->img, x, y, color);
			y++;
		}
		x++;
	}
}

void	put_line()
{
	int	i;

	if (i % map_width != 0)
		//unir cada fcoord[i] amb fcoord[i+1] 
	if (i % map_len != 0)
		//unir cada fcoord[i] amd fcoord[i + width]
	tenir en compte el color
	//my_pixel_put(env->img, x, y, 0x00FF0000);//is going to print a red pixel. Need to create a while loop for all the pixels in our 2D array of 2D that should be printed. 
}

void	my_pixel_put(t_env *img, int x, int y, int color)
{
	int		offset;
	char	*pixel;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	pixel = img->addr + offset;
	*(unsigned int*)pixel = color;
}



