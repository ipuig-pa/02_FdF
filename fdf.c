/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:29:35 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/28 15:33:15 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_env	env;
	
	if (argc!= 2)
		return(ft_printf("Incorrect number of arguments"), 1);
	env.map_file = argv[1];
	if (!init_env(&env))
		return (1);
	get_dimensions(&env);
	parse_map(&env);
	//printf("min_x: %lf, min_y: %lf, max_x: %lf, max_y: %lf\n", env.min_x, env.min_y, env.max_x, env.max_y);
	find_final_coordinates(&env);
	fit_in_window(&env);
	//printf("min_x: %lf, min_y: %lf, max_x: %lf, max_y: %lf\n", env.min_x, env.min_y, env.max_x, env.max_y);
	put_line(&env);
	mlx_put_image_to_window(env.mlx, env.mlx_window, env.img.img, 0, 0);
	mlx_loop(env.mlx);
	//mlx_destroy_window(mlx_window);
	//mlx_destroy_display(mlx);
	//free(mlx);
	//finish_env();
	return (0);
}
