/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:47:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/28 18:33:29 by ipuig-pa         ###   ########.fr       */
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
	column = ft_split(line, ' ');
	while (column[env->map_width])
	{
		free(column[env->map_width]);
		env->map_width++;
	}
	free(column);
	while (line)
	{
		line = get_next_line(fd);
		env->map_height++;
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
				env->coord[(y * env->map_width) + x].color = ft_atoi(*(ft_split(column[x], ',') + 1));
				env->def_color = 1; //si no s-activa la flag de "color definit" en cap moment de la grid, cridar la funcio que transformi z en color.
			}
			else
				env->coord[(y * env->map_width) + x].z = ft_atoi(column[x]);
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
		printf("%i; x0: %i, y0: %i, z0: %i, xf: %lf, yf: %lf\n", i, env->coord[i].x, env->coord[i].y, env->coord[i].z, env->fcoord[i].x, env->fcoord[i].y);
		i++;
	}
	//free(env->coord); no ho puc fer encara si necessito el valor de color per mes endavant
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
	printf("isize: %f, fsize: %f, scale: %f\n", isize, fsize, scale);
	i = 0;
	while (i < (env->map_width * env->map_height))
	{
		printf("pre%i; xf: %lf, yf: %lf\n", i, env->fcoord[i].x, env->fcoord[i].y);
		env->fcoord[i].x = MARGIN + ((env->fcoord[i].x - env->min_x) * scale);
		env->fcoord[i].y = MARGIN + ((env->fcoord[i].y - env->min_y) * scale);
		printf("post%i; xf: %lf, yf: %lf\n", i, env->fcoord[i].x, env->fcoord[i].y);
		i++;
	}
}
//FER QUE QUEDI CENTRAT!!!! (basar-nos en punt mig de finestra i punt mig de dibuix, en lloc de margin agafar aquesta mida de referencia d'alguna manera)

/*	mirar x max - x min. i y max - y min. Encaixar a la finestra fent la transformacio que toqui (translaci'o i escala si cal)
	//faltaria incloude height per calcular que no se'n vagi de la finestra si hi ha pic molt alt o molt baix. 
	o fer-ho diferent! Una vegada tinguem tota la llista de x, y definitiva, escalar segons la mida de la finestra abans de posar-les a la imatge. 
	scalating_in_window
segons mida de grid i alcada trobada en parse_map
ha de retornar una estructura de tipus coordenada (x, y) que sera lorigen de coordenades*/