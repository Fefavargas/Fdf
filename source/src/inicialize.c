/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:02:48 by marvin            #+#    #+#             */
/*   Updated: 2024/11/13 06:31:10 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	inic_proj_min_max(t_fdf *fdf)
{
	fdf->proj.x_proj_max = (float)INT_MIN;
	fdf->proj.y_proj_max = (float)INT_MIN;
	fdf->proj.x_proj_min = (float)INT_MAX;
	fdf->proj.y_proj_min = (float)INT_MAX;
}

void	inic_fdf(t_fdf *fdf, char *file)
{
	fdf->fd = -1;
	fdf->filename = file;
	fdf->camera.z_scale = 0.08;
	inic_proj_min_max(fdf);
	fdf->camera.angle = 30;
	fdf->mlx = NULL;
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		msg_and_exit("Error: mlx inicialize.\n", fdf);
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_W, WINDOW_H, WINDOW_TITLE);
	if (!fdf->win)
		msg_and_exit("Error: window inicialize.\n", fdf);
	fdf->img.img = mlx_new_image(fdf->mlx, WINDOW_W, WINDOW_H);
	if (!fdf->win)
		msg_and_exit("Error: image initializing", fdf);
	fdf->img.data = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp,
			&fdf->img.size_len, &fdf->img.endian);
}

void	init_array(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->map.array = (int ***)ft_calloc(sizeof(int **), fdf->map.y_max);
	if (!fdf->map.array)
		perror_and_exit("Error: malloc array***", fdf);
	i = -1;
	while (++i < fdf->map.y_max)
	{
		fdf->map.array[i] = (int **)ft_calloc(sizeof(int *), fdf->map.x_max);
		if (!fdf->map.array[i])
			perror_and_exit("Error: malloc array**", fdf);
		j = -1;
		while (++j < fdf->map.x_max)
		{
			fdf->map.array[i][j] = (int *)ft_calloc(sizeof(int), 2);
			if (!fdf->map.array[i][j])
				perror_and_exit("Error: malloc array*", fdf);
			fdf->map.array[i][j][0] = 0;
			fdf->map.array[i][j][1] = WIRE_COLOR;
		}
	}
}

void	inic_map_xy_array(t_fdf *fdf)
{
	int		x;
	int		y;
	char	*str;

	open_file(fdf);
	y = 0;
	str = get_next_line(fdf->fd);
	fdf->map.x_max = count_words(str);
	while (str && ++y)
	{
		x = count_words(str);
		if (fdf->map.x_max != x)
		{
			get_next_line(-1);
			free(str);
			perror_and_exit("file not correct!", fdf);
		}
		free(str);
		str = get_next_line(fdf->fd);
	}
	get_next_line(-1);
	close_file(fdf);
	fdf->map.y_max = y;
	init_array(fdf);
}

void	inic_proj(t_fdf *fdf)
{
	int	y;

	y = -1;
	fdf->proj.x_proj = (float **)ft_calloc(fdf->map.y_max, sizeof(float *));
	if (!fdf->proj.x_proj)
		perror_and_exit("malloc array**", fdf);
	fdf->proj.y_proj = (float **)ft_calloc(fdf->map.y_max, sizeof(float *));
	if (!fdf->proj.y_proj)
		perror_and_exit("malloc array**", fdf);
	while (++y < fdf->map.y_max)
	{
		fdf->proj.x_proj[y] = (float *)ft_calloc(fdf->map.x_max, sizeof(float));
		if (!fdf->proj.x_proj[y])
			perror_and_exit("malloc array*", fdf);
		fdf->proj.y_proj[y] = (float *)ft_calloc(fdf->map.x_max, sizeof(float));
		if (!fdf->proj.y_proj[y])
			perror_and_exit("malloc array**", fdf);
	}
}
