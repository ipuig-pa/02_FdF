/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:26:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/29 15:17:59 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <libft.h>
# include <ft_printf.h>
# include <math.h>
# include <fcntl.h>

# include <stdio.h>

# define WINDOW_HEIGHT 1000
# define WINDOW_WIDTH 1020
# define MARGIN (0.01 * WINDOW_WIDTH)
# define DISTX 1
# define DISTY 1
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define BLUE 0x000000FF
# define GREEN 0x0000FF00

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_coord {
	int	x;
	int	y;
	int	z;
	int	color;
}				t_coord;

typedef struct	s_fcoord {
	float	x;
	float	y;
	int		color;
}				t_fcoord;

typedef struct s_env {
	char		*map_file;
	void		*mlx;
	void		*mlx_window;
	t_data		img;
	int			map_width;
	int			map_height;
	int			def_color;
	t_coord		*coord;
	t_fcoord	*fcoord;
	float		min_x;
	float		min_y;
	float		max_x;
	float		max_y;
	int			min_z;
	int			max_z;
}				t_env;

int		init_env(t_env *env);
void	paint_background(t_env *env, int color);
void	my_pixel_put(t_data *img, int x, int y, int color);
void	put_line(t_env *env);
void	join_points(t_env *env, t_fcoord point1, t_fcoord point2);

void	get_dimensions(t_env *env);
void	parse_map(t_env *env);
void	find_final_coordinates(t_env *env);
void	fit_in_window(t_env *env);
void	define_color(t_env *env);

#endif
