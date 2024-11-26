/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:29:35 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/26 17:55:41 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv)
{


	if (argc!= 2)
		return(ft_printf("Incorrect number of arguments"), 1);
	parse_map(argv[1]);

}


int	main(void)
{
	void	*mlx;
	void	*mlx_window;
	t_data	img;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	mlx_window = mlx_new_window(mlx, 1920, 1080, "Render");
	if(!mlx_window)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return (1);
	}
	img.img = mlx_new_image(mlx, 1920, 1080);
	if(!img.img)
	{
		mlx_destroy_window(mlx_window);
		mlx_destroy_display(mlx);
		free(mlx);
		return (1);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_pixel_put(&img, x, y, 0x00FF0000);//is going to print a red pixel. Need to create a while loop for all the pixels in our 2D array of 2D that should be printed. 
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_window(mlx_window);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}

void	parse_map(char map_file, )
{
	int		fd;
	char	*line;

	fd = open(map_file, 0);
	//error handling quan el file no existeixi
	line = get_next_line(fd);
	while (line)
	{
		ft_split(line);
		line = get_next_line(fd);

	}
	close(fd);
}

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int		offset;
	char	*pixel;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	pixel = img->addr + offset;
	*(unsigned int*)pixel = color;
}

