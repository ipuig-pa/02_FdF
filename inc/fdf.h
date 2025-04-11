/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:26:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/04/11 18:03:44 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920
# define DISTX 10
# define DISTY 12
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_coord;

typedef struct s_fcoord
{
	float	x;
	float	y;
	int		color;
}				t_fcoord;

typedef struct s_env
{
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

//manage environment 
void	init_env(t_env *env);
int		key_hook(int keycode, t_env *env);
int		close_window(t_env *env);
void	finish_env(t_env *env, int return_val, char *str);

//get_map_data
void	get_map_dimensions(t_env *env);
void	parse_map(t_env *env);
void	parse_x_and_y(t_env *env, char *line, int y);
void	parse_z_and_color(t_env *env, char *str, int i);

//process_map_data
void	find_final_coordinates(t_env *env);
void	fit_in_window(t_env *env);
void	define_color(t_env *env);

//drawing
void	paint_background(t_env *env, int color);
void	put_line(t_env *env);
void	join_points(t_env *env, t_fcoord point1, t_fcoord point2);
int		interpolate_color(int col1, int col2, float t);
void	my_pixel_put(t_env *env, int x, int y, int color);

//helper
void	free_double_pointer(char **str);
void	handle_allocated_and_finish(t_env *env, char *str);

#endif
