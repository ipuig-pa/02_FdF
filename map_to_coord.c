/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:47:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/27 17:02:24 by ipuig-pa         ###   ########.fr       */
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
		error_handling;
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
		env->map_len++;
	}
	free (line);
	close (fd);
}

void	parse_map(char *map_file, t_env *env)
{
	int		fd;
	char	*line;
	int		x;
	int		y;
	char	**column;

	env->coord = (t_coord *)malloc((env->map_width * env->map_len) * sizeof(t_coord));
	if (!env->coord)
		handle_error();//definir be com fer el handling
	fd = open(map_file, 0); //no cal fer error handling pq si fd <0 ja haurem fet exit a la funcio de get dimenstions amb handle error
	line = get_next_line(fd);
	y = 0;
	while (line)
	{
		column = ft_split(line, ' ');
		x = 0;
		while (column[x])
		{
			if (ft_strchr(column[x], ','))
			{
				env->coord[x + y].z = ft_atoi(*ft_split(column[x], ','));
				env->coord[x + y].color = ft_atoi(*(ft_split(column[x], ',') + 1));//incloure d-alguna manera alguna flag per saber si en tot el mapa hi ha algun color o cap ha de ser de color, o li he de fer gradient(?)
				//si no s-activa la flag de "color definit" en cap moment de la grid, cridar la funcio que transformi z en color.
			}
			else
				env->z = ft_atoi(column[x]);
			env->coord[x + y].x = i;
			env->coord[x + y].y = y;
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

	env->fcoord = (t_fcoord *)malloc((env->map_width * env->map_len) * sizeof(t_foord));
	if (!env->fcoord)
		handle_error();//definir be com fer el handling
	i = 0;
	env->min_x = env->fcoord[i].x;
	env->max_x = env->fcoord[i].x;
	env->min_y = env->fcoord[i].y;
	env->max_y = env->fcoord[i].y;
	while (i < (env->map_width * env->map_len))
	{
		env->fcoord[i].x = 90 / 11 * env->coord[i].x * cos(M_PI / 6) - (90 / 11 * env->cord[i].y * sin(M_PI / 3));
		env->fcoord[i].y = - 90 / 11 * env->coord[i].y * sin(M_PI / 6) - (90/11 * env->cord[i].x * sin(M_PI / 6)) + 90 / 11 * env->coord[i].z;
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
	//free(env->coord); no ho puc fer encara si necessito el valor de color per mes endavant
}

void	fit_in_window(t_env *env)
{
	int	w;
	int	h;

	w = env->max_x - env->min_x;
	h = env->max_y - env->min_y;
	if (w > WINDOW_WIDTH)
		scale = WINDOW_WIDTH / w; //buscar be basant tant en x com en y
	while (i < (env->map_width * env->map_len)) // que aixo nomes ho faci si escale o transloc es necessari
	{
		env->fcoord[i].x = env->fcoord[i].x + scale 
	}
	mirar x max - x min. i y max - y min. Encaixar a la finestra fent la transformacio que toqui (translaci'o i escala si cal)
	//faltaria incloude height per calcular que no se'n vagi de la finestra si hi ha pic molt alt o molt baix. 
	o fer-ho diferent! Una vegada tinguem tota la llista de x, y definitiva, escalar segons la mida de la finestra abans de posar-les a la imatge. 
	scalating_in_window
segons mida de grid i alcada trobada en parse_map
ha de retornar una estructura de tipus coordenada (x, y) que sera lorigen de coordenades
}
