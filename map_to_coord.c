/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:47:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/30 12:29:30 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_dimensions(t_env *env)
{
	int		fd;
	char	*line;
	char	**column;

	fd = open(env->map_file, 0);
	if (fd < 0)
		finish_env(env, 1, "File doesn't exist or permission denied\n");
	line = get_next_line(fd);
	if (!line)
		finish_env(env, 1, "Empty file or not properly formatted\n");
	column = ft_split(line, ' ');
	while (column[env->map_width])
	{
		free(column[env->map_width]);
		env->map_width++;
	}
	free(column);
	while (line)
	{
		free (line);
		line = get_next_line(fd);
		env->map_height++;
	}
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
	if (!env->coord)
		finish_env(env, 1, "Malloc fail\n");
	fd = open(env->map_file, 0);
	line = get_next_line(fd);
	y = 0;
	env->def_color = 0;
	while (line)
	{
		column = ft_split(line, ' ');
		x = 0;
		while (column[x])
		{
			parse_z_and_color(env, column[x], (y * env->map_width) + x);
			env->coord[(y * env->map_width) + x].x = x;
			env->coord[(y * env->map_width) + x].y = y;
			free (column[x]);
			x++;
		}
		free (line);
		free (column);
		line = get_next_line(fd);
		y++;
	}
	free(line);
	close(fd);
}

void	parse_z_and_color(t_env *env, char *str, int i)
{
	char	**split;
	char	*color;
	int		j;
	char	c;
	static int		lower;

	if (ft_strchr(str, ','))
	{
		split = ft_split(str, ',');
		if (!split)
			finish_env(env, 1, "Malloc fail\n");
		env->coord[i].z = ft_atoi(*split);
		color = ft_substr(split[1], 2, 8);
		if (!color)
		{
			j = 0;
			while (split[j])
			{
				free(split[j]);
				j++;
			}
			finish_env(env, 1, "Malloc fail\n");
		}
		if (lower == 0)
		{
			c = 'a';
			while (c <= 'f')
			{
				if (ft_strchr(color, c))
					lower = 1;
				c++;
			}
			c = 'A';
			while (c <= 'F')
			{
				if (ft_strchr(color, c))
					lower = -1;
				c++;
			}
		}
		if (lower == 1)
			env->coord[i].color = ft_atoi_base(color, "0123456789abcdef");
		else
			env->coord[i].color = ft_atoi_base(color, "0123456789ABCDEF");
		j = 0;
		while (split[j])
		{
			free(split[j]);
			j++;
		}
		free(split);
		free(color);
		env->def_color = 1;
	}
	else
	{
		env->coord[i].z = ft_atoi(str);
		env->coord[i].color = WHITE;
	}
}

void	find_final_coordinates(t_env *env)
{
	int	i;

	env->fcoord = (t_fcoord *)malloc((env->map_width * env->map_height) * sizeof(t_fcoord));
	if (!env->fcoord)
		finish_env(env, 1, "Malloc fail\n");
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
	scale = (fsize - (2 * 0.01 * fsize)) / isize;
	i = 0;
	while (i < (env->map_width * env->map_height))
	{
		env->fcoord[i].x = ((WINDOW_WIDTH / 2) - ((env->max_x - env->min_x) / 2) * scale) + ((env->fcoord[i].x - env->min_x) * scale);
		env->fcoord[i].y = ((WINDOW_HEIGHT / 2) - ((env->max_y - env->min_y) / 2) * scale) + ((env->fcoord[i].y - env->min_y) * scale);
		i++;
	}
}


