/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:50:55 by marvin            #+#    #+#             */
/*   Updated: 2024/11/11 13:53:51 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_extrema(t_fdf *fdf, int angle)
{
	int		x;
	int		y;
	float	x_proj;
	float	y_proj;

	y = -1;
	while (++y < fdf->map.y_max)
	{
		x = -1;
		while (++x < fdf->map.x_max)
		{
			x_proj = (x - y) * cos(angle * M_PI / 180);
			y_proj = (x + y) * sin(angle * M_PI / 180) - fdf->map.array[y][x][0] * fdf->camera.z_scale;
			fdf->proj.x_proj_max = ft_bigger_float(x_proj, fdf->proj.x_proj_max);
			if (x_proj < fdf->proj.x_proj_min)
				fdf->proj.x_proj_min = x_proj;
			fdf->proj.y_proj_max = ft_bigger_float(y_proj, fdf->proj.y_proj_max);
			if (y_proj < fdf->proj.y_proj_min)
				fdf->proj.y_proj_min = y_proj;
		}
	}
}

static void	get_scale(t_fdf *fdf, int angle)
{
	float	x_range;
	float	y_range;
	float	x_scale;
	float	y_scale;
	float	scale;

	get_extrema(fdf, angle);
	x_range = fdf->proj.x_proj_max - fdf->proj.x_proj_min;
	y_range = fdf->proj.y_proj_max - fdf->proj.y_proj_min;
	x_scale = WINDOW_W / x_range * SCREEN_UTIL;
	y_scale = WINDOW_H / y_range * SCREEN_UTIL;
	scale = y_scale;
	if (x_scale < y_scale)
		scale = x_scale;
	fdf->camera.scale = scale;
}

static void	get_offset(t_fdf *fdf)
{
	float	x_range;
	float	y_range;
	float	x_offset;
	float	y_offset;

	x_range = fdf->proj.x_proj_max - fdf->proj.x_proj_min;
	y_range = fdf->proj.y_proj_max - fdf->proj.y_proj_min;
	x_offset = (WINDOW_W - (x_range * fdf->camera.scale)) / 2;
	fdf->camera.x_offset = x_offset;
	y_offset = (WINDOW_H - (y_range * fdf->camera.scale)) / 2;
	fdf->camera.y_offset = y_offset;
}

void	project(t_fdf *fdf, int angle)
{
	int		x;
	int		y;
	float	x_proj;
	float	y_proj;
	float	z_proj;

	y = -1;
	black_background(fdf);
	inic_proj_min_max(fdf);
	get_scale(fdf, angle);
	get_offset(fdf);
	while (++y < fdf->map.y_max)
	{
		x = -1;
		while (++x < fdf ->map.x_max)
		{
			z_proj = fdf->map.array[y][x][0];
			x_proj = (((x - y) * cos(angle * M_PI / 180)) - fdf->proj.x_proj_min) * fdf->camera.scale + fdf->camera.x_offset;
			y_proj = (((x + y) * sin(angle * M_PI / 180) - z_proj * fdf->camera.z_scale)
							- fdf->proj.y_proj_min) * fdf->camera.scale + fdf->camera.y_offset;
			fdf->proj.x_proj[y][x] = x_proj;
			fdf->proj.y_proj[y][x] = y_proj;
		}
	}
}

// void	ft_rotate_x(int *y, int *z, double x_angle)
// {
// 	int	prev_y;

// 	prev_y = *y;
// 	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
// 	*z = prev_y * (-sin(x_angle)) + *z * cos(x_angle);
// }

// void	ft_rotate_y(int *x, int *z, double y_angle)
// {
// 	int	prev_x;

// 	prev_x = *x;
// 	*x = prev_x * cos(y_angle) + *z * sin(y_angle);
// 	*z = prev_x * sin(y_angle) + *z * cos(y_angle);
// }

// void	ft_rotate_z(int *x, int *y, double z_angle)
// {
// 	int	prev_x;
// 	int	prev_y;

// 	prev_x = *x;
// 	prev_y = *y;
// 	*x = prev_x * cos(z_angle) - prev_y * sin(z_angle);
// 	*y = prev_x * sin(z_angle) + prev_y * cos(z_angle);
// }

// void	iso(float *x, float *y, int z)
// {
// 	float	prev_x;
// 	float	prev_y;

// 	printf("->> x =%f,  y =%f,  z =%i -<<", *x, *y, z);
// 	prev_x = *x;
// 	prev_y = *y;
// 	*x = (prev_x - prev_y) * cos(0.523599);
// 	*y = (prev_x + prev_y) * sin(0.523599) - z;
// 	printf(" point x =%f,  point y =%f,  point z =%d", *x, *y, z);
// }