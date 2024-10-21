/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:17:29 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 19:20:42 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_zoom(int buttom, t_fdf *fdf)
{
	if (buttom == MOUSE_WHEEL_UP)
		fdf->camera->zoom += 2;
	else if (buttom == MOUSE_WHEEL_DOWN)
		fdf->camera->zoom -= 2;
	if (fdf->camera->zoom < 1)
		fdf->camera->zoom = 1;
	ft_draw(fdf);
}

int	ft_mouse(int buttom, int x, int y, t_fdf *fdf)
{
	if (buttom == MOUSE_WHEEL_UP || buttom == MOUSE_WHEEL_DOWN)
		ft_zoom(buttom, fdf);
	else if (buttom == MOUSE_CLICK_LEFT || buttom == MOUSE_CLICK_RIGHT 
				|| buttom == MOUSE_CLICK_MIDDLE)
	{
		fdf->mouse->button = buttom;
		fdf->mouse->x = x;
		fdf->mouse->y = y;
	}
	return (0);
}

void	ft_move_z(int x, int y, t_fdf *fdf)
{
	if (x < (WINDOW_W / 2) + fdf->camera->x_offset)
		fdf->camera->z_angle -= (y - fdf->mouse->y) * 0.002;
	else
		fdf->camera->z_angle += (y - fdf->mouse->y) * 0.002;
}

int	ft_mouse_move(int x, int y, t_fdf *fdf)
{
	if (fdf->mouse->button == MOUSE_CLICK_RIGHT)
	{
		fdf->camera->x_angle += (y - fdf->mouse->y) * 0.002;
		fdf->camera->y_angle += (x - fdf->mouse->x) * 0.002;
	}
	else if (fdf->mouse->button == MOUSE_CLICK_LEFT)
	{
		fdf->camera->x_offset += x - fdf->mouse->x;
		fdf->camera->y_offset += y - fdf->mouse->y;
	}
	else if (fdf->mouse->button == MOUSE_CLICK_MIDDLE)
		ft_move_z(x, y, fdf);
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	ft_draw(fdf);
	return (0);
}

int	ft_close_win(t_fdf *fdf)
{
	int		x;
	int		y;

	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf->camera);
	free(fdf->mouse);
	y = -1;
	while (++y < fdf->map->y)
	{
		x = -1;
		while (++x < fdf->map->x)
			free(fdf->map->array[y][x]);
		free(fdf->map->array[y]);
	}
	free(fdf->map->array);
	free(fdf->map);
	free(fdf->mlx);
	free(fdf);
	exit(0);
}
