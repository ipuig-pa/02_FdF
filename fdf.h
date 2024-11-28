/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:26:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/28 13:45:50 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <libft.h>
# include <ft_printf.h>
# include <math.h>
# include <fcntl.h>

# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF

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
	double	x;
	double	y;
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
	double		min_x;
	double		min_y;
	double		max_x;
	double		max_y;
}				t_env;


int		init_env(t_env *env);
void	paint_background(t_env *env, int color);
void	my_pixel_put(t_data *img, int x, int y, int color);
void	put_line(t_env *env);
void	join_points(t_env *env, int x1, int y1, int x2, int y2);

void	get_dimensions(t_env *env);
void	parse_map(t_env *env);
void	find_final_coordinates(t_env *env);
//void	fit_in_window(t_env *env);

#endif
