/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:18:47 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/30 00:11:20 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_value(char *str, int y, t_fdf *fdf)
{
	char	**array;
	int		i;
	int		j;

	array = ft_split(str, ' ');
	i = -1;
	while (array[++i])
	{
		fdf->map->array[i][y -1][0] = ft_atoi(array[i]);
		j = 0;
		while (array[i][j] && array[i][j] != ',')
			j++;
		if (array[i][j] == ',')
			fdf->map->array[i][y -1][1] = get_color(&array[i][++j]);
		else
			fdf->map->array[i][y -1][1] = -1;
	}
}

void	get_values_map(t_fdf *fdf)
{
	char	*str;
	int		y;

	if (!open_file(fdf))
		error("open file error");
	str = get_next_line(fdf->fd);
	y = 0;
	while (str && ++y)
	{
		get_value(str, y, fdf);
		free(str);
		str = get_next_line(fdf->fd);
	}
	get_next_line(-1);
	close(fdf->fd);
}

void	read_file(t_fdf *fdf)
{
	inic_map_xy_array(fdf);
	get_values_map(fdf);
	ft_putstr_fd("here1\n", 1);
	ft_z_min_max(fdf);
}

void	inicialize(t_fdf *fdf)
{
	t_image	*img;

	fdf = NULL;
	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		error("malloc fdf");
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		error("connecting graphic error");
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF - fefa");
	if (!fdf->win)
		error("window initializing error");
	fdf->img = (t_image *)ft_calloc(1, sizeof(t_image));
	if (!fdf->img)
		error("malloc image");
	fdf->img->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img->img)
		error("image initializing error");
	img = fdf->img;
	img->data_addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_len, &img->endian);
	fdf->map = NULL;
	fdf->camera = NULL;
	fdf->mouse = (t_mouse *)ft_calloc(sizeof(t_mouse), 1);
	if (!fdf->mouse)
		error("mouse initializing error");
}

void	inic_map(t_fdf *fdf, char *filename)
{
	fdf->map = (t_map *)ft_calloc(sizeof(t_map), 1);
	if (!fdf->map)
		error("malloc map");
	fdf->map->array = NULL;
	fdf->filename = filename;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (0);
	inicialize(&fdf);
	inic_map(&fdf, argv[1]);
	read_file(&fdf);
	init_camera(&fdf);
	ft_putstr_fd("40-you are here\n", 1);
	hook_control(&fdf);
	ft_putstr_fd("50-you are here\n", 1);
	ft_draw(&fdf);
	mlx_loop((&fdf)->mlx);
	return (0);
}
