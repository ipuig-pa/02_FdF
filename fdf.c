/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:29:35 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/29 18:51:54 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		return (ft_printf("Incorrect number of arguments\n"), 1);
	env.map_file = argv[1];
	init_env(&env);
	env.map_height = 0;
	env.map_width = 0;
	get_dimensions(&env);
	parse_map(&env);
	find_final_coordinates(&env);
	fit_in_window(&env);
	define_color(&env);
	put_line(&env);
	mlx_put_image_to_window(env.mlx, env.mlx_window, env.img.img, 0, 0);
	//mlx_mouse_hook(env.mlx_window, mouse_hook, &env);
	mlx_hook(env.mlx_window, 2, 1L<<0, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
