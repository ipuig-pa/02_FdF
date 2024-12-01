/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:47:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/01 10:29:53 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_map_dimensions(t_env *env)
{
	int		fd;
	char	*line;
	char	**column;

	fd = open(env->map_file, 0);
	if (fd < 0)
		finish_env(env, 1, "File doesn't exist or permission denied\n");
	line = get_next_line(fd);
	if (!line)
		finish_env(env, 1, "Empty map\n");
	column = ft_split(line, ' ');
	if (!column)
		handle_allocated_and_finish(env, line);
	while (column[env->map_width] && column[env->map_width][0] != '\n')
		env->map_width++;
	free_double_pointer(column);
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
	int		y;

	fd = open(env->map_file, 0);
	line = get_next_line(fd);
	if (!line)
		finish_env(env, 1, "Malloc fail\n");
	y = 0;
	while (line)
	{
		parse_x_and_y(env, line, y);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
}

void	parse_x_and_y(t_env *env, char *line, int y)
{
	int		x;
	char	**column;

	column = ft_split(line, ' ');
	if (!column)
		handle_allocated_and_finish(env, line);
	x = 0;
	while (column[x])
	{
		parse_z_and_color(env, column[x], (y * env->map_width) + x);
		env->coord[(y * env->map_width) + x].x = x;
		env->coord[(y * env->map_width) + x].y = y;
		x++;
	}
	free (line);
	free_double_pointer(column);
}

void	parse_z_and_color(t_env *env, char *str, int i)
{
	char	**split;
	char	*color;

	if (ft_strchr(str, ','))
	{
		split = ft_split(str, ',');
		if (!split)
			finish_env(env, 1, "Malloc fail\n");
		env->coord[i].z = ft_atoi(*split);
		color = ft_substr(split[1], 2, 8);
		if (!color)
		{
			free_double_pointer(split);
			finish_env(env, 1, "Malloc fail\n");
		}
		env->coord[i].color = ft_atoi_hex(color);
		free_double_pointer(split);
		free(color);
		env->def_color = 1;
	}
	else
	{
		env->coord[i].z = ft_atoi(str);
		env->coord[i].color = WHITE;
	}
}
