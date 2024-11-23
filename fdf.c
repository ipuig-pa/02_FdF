/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:29:35 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/23 17:00:59 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_window;
	void	*img;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 1920, 1080, "Render");
	mlx_loop(mlx);
	img = mlx_new_image(mlx, 1920, 1080);
	
}

parse_map

draw

