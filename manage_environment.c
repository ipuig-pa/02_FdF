/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:23:48 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/30 12:26:57 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_env(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		finish_env(env, 1, "Environment can not be initalized\n");
	env->mlx_window = mlx_new_window(env->mlx, WINDOW_WIDTH, \
					WINDOW_HEIGHT, env->map_file);
	if (!env->mlx_window)
		finish_env(env, 1, "Environment can not be initalized\n");
	env->img.img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!env->img.img)
		finish_env(env, 1, "Environment can not be initalized\n");
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel, \
					&env->img.line_length, &env->img.endian);
	if (!env->img.addr)
		finish_env(env, 1, "Environment can not be initalized\n");
	paint_background(env, BLACK);
}

/*int	mouse_hook(int mousecode, t_env *env)
{
	if (mousecode == 4)
		zoom_in();
	else if (mousecode == 5)
		zoom_out();
	return (0);
}*/

int	key_hook(int keycode, t_env *env)
{
	if (keycode == 53)
		return (finish_env(env, 0, "Esc pressed"), 0);
	return (0);
}

//Add "mlx_destroy_display(env->mlx);" before freeing in Linux environments
void	finish_env(t_env *env, int return_val, char *str)
{
	ft_printf("%s\n", str);
	if (env)
	{
		if (env->coord)
			free(env->coord);
		if (env->fcoord)
			free(env->fcoord);
		if (env->img.img)
			mlx_destroy_image(env->mlx, env->img.img);
		if (env->mlx_window)
			mlx_destroy_window(env->mlx, env->mlx_window);
		if (env->mlx)
			free(env->mlx);
	}
	exit (return_val);
}

