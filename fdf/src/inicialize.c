/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:02:48 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 17:25:18 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int init_array(t_fdf *fdf)
{
	int	i;

	fdf->map->array = (int ***)ft_calloc(sizeof(int **), fdf->map->x);
	if (!fdf->map->array)
		return (0);
	i = 0;
	while (i < fdf->map->x)
	{
		fdf->map->array[i] = (int **)ft_calloc(sizeof(int *), 2);
		if (!fdf->map->array[i])
			return (0);
		i++;
	}
	return (1);
}

int	init_map(t_fdf *fdf)
{
	int		x;
	int		y;
	char	*str;

	if (!open_file(fdf))
		return (0);
	while (str = get_next_line(fdf->fd))
	{
		x = count_words(str);
		if (fdf->map->x == 0)
			fdf->map->x = x;
		else if (fdf->map->x != x)
		{
			get_next_line(-1);
			return (0);
		}
		y++;
	}
	get_next_line(-1);
	close(fdf->fd);
	fdf->map->y = y;
	return (init_array(fdf));
}

int	init_mlx(t_fdf	*fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (0);
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_W, WINDOW_H, WINDOW_TITLE);
	if (!fdf->win)
		return (0);
	fdf->img->img = mlx_new_image(fdf->mlx, WINDOW_W, WINDOW_H);
	if (!fdf->img->img)
		return (0);
	fdf->img->data = mlx_get_data_addr(fdf->img->img, &fdf->img->bpp, &fdf->img->size_len, 
						&fdf->img->endian);
	if (!fdf->img->data)
		return (0);
	return (1);
}

int	init_camera(t_fdf *fdf)
{
	t_camera	*camera;

	camera = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (0);
	camera->zoom = WINDOW_H / fdf->map->x / 2;
	camera->x_angle = -0.615472907;
	camera->y_angle = -0.523599;
	camera->z_angle = 0.615472907;
	camera->z_height = 1;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->iso = 1;
	fdf->camera = camera;
	return (1);
}

