/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:48:58 by fefa              #+#    #+#             */
/*   Updated: 2024/11/11 13:49:11 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_mlx(t_fdf *fdf)
{
	if (fdf->mlx)
	{
		if (fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		if (fdf->img.img)
			mlx_destroy_image(fdf->mlx, fdf->img.img);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
		fdf->win = NULL;
		fdf->img.img = NULL;
		fdf->img.data = NULL;
		fdf->mlx = NULL;
	}
}

static void	free_int_array(t_fdf *fdf)
{
	int	y;
	int	x;

	if (!fdf->map.array)
		return ;
	y = -1;
	while (++y < fdf->map.y_max)
	{
		x = -1;
		while (++x < fdf->map.x_max)
			free(fdf->map.array[y][x]);
		free(fdf->map.array[y]);
	}
	free(fdf->map.array);
}

static void	free_float_arr(float ***array_ptr, t_fdf *fdf)
{
	int		y;
	float	**array;

	y = -1;
	array = *array_ptr;
	if (!array)
		return ;
	while (++y < fdf->map.y_max)
		free(array[y]);
	free(array);
	*array_ptr = NULL;
}

void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	free_mlx(fdf);
	close (fdf->fd);
	free_int_array(fdf);
	free_float_arr(&fdf->proj.x_proj, fdf);
	free_float_arr(&fdf->proj.y_proj, fdf);
}

void	free_str_arr(char **array)
{
	int		i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}
