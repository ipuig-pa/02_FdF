/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:29:35 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/30 19:21:46 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		return (ft_printf("Incorrect number of arguments"), 1);
	ft_memset(&env, 0, sizeof(t_env));
	env.map_file = argv[1];
	get_dimensions(&env);
	init_env(&env);
	parse_map(&env);
	find_final_coordinates(&env);
	fit_in_window(&env);
	define_color(&env);
	put_line(&env);
	mlx_put_image_to_window(env.mlx, env.mlx_window, env.img.img, 0, 0);
	mlx_hook(env.mlx_window, 17, 0, close_window, &env);
	mlx_hook(env.mlx_window, 2, 1L << 0, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
