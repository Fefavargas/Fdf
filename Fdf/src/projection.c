/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:50:55 by marvin            #+#    #+#             */
/*   Updated: 2024/10/12 20:50:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_x(int *y, int *z, double x_angle)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
	*z = prev_y * (-sin(x_angle)) + *z * cos(x_angle);
}

void	ft_rotate_y(int *x, int *z, double y_angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(y_angle) + *z * sin(y_angle);
	*z = prev_x * sin(y_angle) + *z * cos(y_angle);
}

void	ft_rotate_z(int *x, int *y, double z_angle)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(z_angle) - prev_y * sin(z_angle);
	*y = prev_x * sin(z_angle) + prev_y * cos(z_angle);
}

t_point	project(int x, int y, t_fdf *fdf)
{
    t_point	point;
	
	if (fdf->map->array[x][y][1] > 0)
		point.color = fdf->map->array[x][y][1];
	point.z = fdf->map->array[x][y][0];
	point.z *= fdf->camera->zoom / fdf->camera->z_height;
	point.x = x * fdf->camera->zoom;
	point.y = y * fdf->camera->zoom;
	ft_rotate_x(&point.y, &point.z, fdf->camera->x_angle);
	ft_rotate_y(&point.x, &point.z, fdf->camera->y_angle);
	ft_rotate_z(&point.x, &point.y, fdf->camera->z_angle);
	point.x += WINDOW_W / 2 + fdf->camera->x_offset;
	point.y += (WINDOW_H + fdf->map->y * fdf->camera->zoom) / 2 + fdf->camera->y_offset;
	return (point);
}