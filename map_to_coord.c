/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:47:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/29 15:24:10 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_dimensions(t_env *env)
{
	int		fd;
	char	*line;
	char	**column;

	fd = open(env->map_file, 0);
	/*if (fd < 0)
		error_handling;*/
	line = get_next_line(fd);
	// if (!line)
	// 	error_handling;
	env->map_height = 0;
	env->map_width = 0;
	column = ft_split(line, ' ');
	while (column[env->map_width])
	{
		free(column[env->map_width]);
		env->map_width++;
	}
	free(column);
	//ft_printf("count: %i; %s", env->map_height, line);
	while (line)
	{
		line = get_next_line(fd);
		env->map_height++;
		//ft_printf("count: %i; %s", env->map_height, line);
	}
	free (line);
	close (fd);
}

void	parse_map(t_env *env)
{
	int		fd;
	char	*line;
	int		x;
	int		y;
	char	**column;

	env->coord = (t_coord *)malloc((env->map_width * env->map_height) * sizeof(t_coord));
	/*if (!env->coord)
		handle_error();//definir be com fer el handling*/
	fd = open(env->map_file, 0); //no cal fer error handling pq si fd <0 ja haurem fet exit a la funcio de get dimenstions amb handle error
	line = get_next_line(fd);
	y = 0;
	env->def_color = 0;
	while (line)
	{
		column = ft_split(line, ' ');
		x = 0;
		while (column[x])
		{
			//revisar aquesta part
			if (ft_strchr(column[x], ','))
			{
				env->coord[(y * env->map_width) + x].z = ft_atoi(*ft_split(column[x], ','));
				env->coord[(y * env->map_width) + x].color = ft_atoi_base(ft_substr(*(ft_split(column[x], ',') + 1), 2, 6), "0123456789ABCDEF");
				ft_printf("i: %i, color: %X\n", (y * env->map_width) + x, env->coord[(y * env->map_width) + x].color);
				env->def_color = 1; //si no s-activa la flag de "color definit" en cap moment de la grid, cridar la funcio que transformi z en color.
			}
			else
			{
				env->coord[(y * env->map_width) + x].z = ft_atoi(column[x]);
				env->coord[(y * env->map_width) + x].color = WHITE;
			}
			env->coord[(y * env->map_width) + x].x = x;
			env->coord[(y * env->map_width) + x].y = y;
			//ft_printf("%i; x: %i, y: %i, z: %i\n", (y * env->map_width) + x, env->coord[(y * env->map_width) + x].x, env->coord[(y * env->map_width) + x].y, env->coord[(y * env->map_width) + x].z);
			x++;
		}
		line = get_next_line(fd);
		y++;
	}
	free(column);
	free(line);
	close(fd);
}

void	find_final_coordinates(t_env *env)
{
	int	i;

	env->fcoord = (t_fcoord *)malloc((env->map_width * env->map_height) * sizeof(t_fcoord));
	/*if (!env->fcoord)
		handle_error();//definir be com fer el handling*/
	i = 0;
	env->min_x = 9.0 / 11 * DISTX * env->coord[i].x * cos(M_PI / 6) - (9.0 / 11 * DISTY * env->coord[i].y * sin(M_PI / 3));
	env->max_x = env->min_x;
	env->min_y = 9.0 / 11 * DISTY * env->coord[i].y * sin(M_PI / 6) + (9.0 / 11 * DISTX * env->coord[i].x * sin(M_PI / 6)) - 9.0 / 11 * env->coord[i].z;
	env->max_y = env->min_y;
	while (i < (env->map_width * env->map_height))
	{
		env->fcoord[i].x = 9.0 / 11 * DISTX * env->coord[i].x * cos(M_PI / 6) - (9.0 / 11 * DISTY * env->coord[i].y * sin(M_PI / 3));
		env->fcoord[i].y = 9.0 / 11 * DISTY * env->coord[i].y * sin(M_PI / 6) + (9.0 / 11 * DISTX * env->coord[i].x * sin(M_PI / 6)) - 9.0 / 11 * env->coord[i].z;
		if (env->fcoord[i].x < env->min_x)
			env->min_x = env->fcoord[i].x;
		else if (env->fcoord[i].x > env->max_x)
			env->max_x = env->fcoord[i].x;
		if (env->fcoord[i].y < env->min_y)
			env->min_y = env->fcoord[i].y;
		else if (env->fcoord[i].y > env->max_y)
			env->max_y = env->fcoord[i].y;
		//printf("%i; x0: %i, y0: %i, z0: %i, xf: %lf, yf: %lf\n", i, env->coord[i].x, env->coord[i].y, env->coord[i].z, env->fcoord[i].x, env->fcoord[i].y);
		i++;
	}
	//free(env->coord); no ho puc fer encara si necessito el valor de color per mes endavant
}

void	define_color(t_env *env)
{
	int	i;

	i = 0;
	env->min_z = env->coord[i].z;
	env->max_z = env->coord[i].z;
	if (env->def_color == 0)
	{
		while (i < (env->map_width * env->map_height))
		{
			if (env->coord[i].z < env->min_z)
				env->min_z = env->coord[i].z;
			else if (env->coord[i].z > env->max_z)
				env->max_z = env->coord[i].z;
			i++;
		}
	}
	i = 0;
	while (i < (env->map_width * env->map_height))
	{
		if (env->def_color == 1)
			env->fcoord[i].color = env->coord[i].color;
		else
			env->fcoord[i].color = (env->coord[i].z - env->min_z) * ((RED - WHITE) / (env->max_z - env->min_z)) + WHITE;
		i++;
	}
}

void	fit_in_window(t_env *env)
{
	float		isize;
	float		fsize;
	float		scale;
	int			i;

	isize = (env->max_y - env->min_y);
	fsize = WINDOW_HEIGHT;
	if ((float)((env->max_x - env->min_x) / (env->max_y - env->min_y)) > ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT))
	{
		isize = (env->max_x - env->min_x);
		fsize = WINDOW_WIDTH;
	}
	scale = (fsize - (2 * MARGIN)) / isize;
	//printf("isize: %f, fsize: %f, scale: %f\n", isize, fsize, scale);
	i = 0;
	while (i < (env->map_width * env->map_height))
	{
		//printf("pre%i; xf: %lf, yf: %lf\n", i, env->fcoord[i].x, env->fcoord[i].y);
		env->fcoord[i].x = ((WINDOW_WIDTH / 2) - ((env->max_x - env->min_x) / 2) * scale) + ((env->fcoord[i].x - env->min_x) * scale);
		env->fcoord[i].y = ((WINDOW_HEIGHT / 2) - ((env->max_y - env->min_y) / 2) * scale) + ((env->fcoord[i].y - env->min_y) * scale);
		//printf("post%i; xf: %lf, yf: %lf\n", i, env->fcoord[i].x, env->fcoord[i].y);
		i++;
	}
}
