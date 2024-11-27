/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:26:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/27 16:50:52 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <libft.h>
# include <ft_printf.h>
# include <math.h>

WINDOW_HEIGHT 1080;
WINDOW_WIDTH 1920;
BLACK 0x00000000;
WHITE 0x00FFFFFF;

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
	int			map_length;
	t_coord		*coord;
	t_fcoord	*fcoord;
}				t_env;

#endif
