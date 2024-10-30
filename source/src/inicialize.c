/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:02:48 by marvin            #+#    #+#             */
/*   Updated: 2024/10/30 00:10:19 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_array(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->map->array = (int ***)ft_calloc(sizeof(int **), fdf->map->x);
	if (!fdf->map->array)
		error("malloc array***");
	i = -1;
	while (++i < fdf->map->x)
	{
		fdf->map->array[i] = (int **)ft_calloc(sizeof(int *), fdf->map->y);
		if (!fdf->map->array[i])
			error("malloc array**");
		j = -1;
		while (++j < fdf->map->y)
		{
			fdf->map->array[i][j] = (int *)ft_calloc(sizeof(int), 2);
			if (!fdf->map->array[i][j])
				error("malloc array*");
			fdf->map->array[i][j][0] = 0;
			fdf->map->array[i][j][1] = 0;
		}
	}
}

void	inic_map_xy_array(t_fdf *fdf)
{
	int		x;
	int		y;
	char	*str;

	if (!open_file(fdf))
		error("open file error");
	y = 0;
	str = get_next_line(fdf->fd);
	fdf->map->x = count_words(str);
	while (str && ++y)
	{
		x = count_words(str);
		if (fdf->map->x != x)
		{
			get_next_line(-1);
			free(str);
			error("file not correct!");
		}
		free(str);
		str = get_next_line(fdf->fd);
	}
	get_next_line(-1);
	close(fdf->fd);
	fdf->map->y = y;
	init_array(fdf);
}

void	init_camera(t_fdf *fdf)
{
	t_camera	*camera;

	camera = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (!camera)
		error("malloc camera");
	camera->zoom = ft_min(HEIGHT / fdf->map->y / 2, WIDTH / fdf->map->x / 2);
	camera->x_angle = -0.615472907;
	camera->y_angle = -0.523599;
	camera->z_angle = 0.615472907;
	camera->z_height = 1;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->iso = 1;
	fdf->camera = camera;
}

