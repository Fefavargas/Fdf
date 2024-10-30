/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:17:29 by marvin            #+#    #+#             */
/*   Updated: 2024/10/30 18:58:24 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_zoom(int button, t_fdf *fdf)
{
	if (button == MOUSE_WHEEL_UP)
		fdf->camera->zoom += 2;
	else if (button == MOUSE_WHEEL_DOWN)
		fdf->camera->zoom -= 2;
	if (fdf->camera->zoom < 1)
		fdf->camera->zoom = 1;
	ft_draw(fdf);
}

int	ft_mouse(int button, int x, int y, void *params)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)params;
	if (button == MOUSE_WHEEL_UP || button == MOUSE_WHEEL_DOWN)
		ft_zoom(button, fdf);
	else if (button == MOUSE_CLICK_LEFT || button == MOUSE_CLICK_RIGHT
		|| button == MOUSE_CLICK_MIDDLE)
	{
		fdf->mouse->button = button;
		fdf->mouse->x = x;
		fdf->mouse->y = y;
	}
	return (0);
}

void	ft_move_z(int x, int y, t_fdf *fdf)
{
	if (x < (WIDTH / 2) + fdf->camera->x_offset)
		fdf->camera->z_angle -= (y - fdf->mouse->y) * 0.002;
	else
		fdf->camera->z_angle += (y - fdf->mouse->y) * 0.002;
}

int	ft_mouse_move(int x, int y, void *params)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)params;
	if (fdf->mouse->button == MOUSE_CLICK_RIGHT)
	{
		fdf->camera->x_angle += (y - fdf->mouse->prev_y) * 0.002;
		fdf->camera->y_angle += (x - fdf->mouse->prev_x) * 0.002;
		//fdf->camera->x_angle = ft_reset_angles(fdf->camera->x_angle);
		//fdf->camera->y_angle = ft_reset_angles(fdf->camera->y_angle);
		fdf->mouse->prev_x = x;
		fdf->mouse->prev_y = y;
		ft_draw(fdf);
	}
	else if (fdf->mouse->button == MOUSE_CLICK_LEFT)
	{
		fdf->camera->x_offset += (x - fdf->mouse->prev_x);
		fdf->camera->y_offset += (y - fdf->mouse->prev_y);
		fdf->mouse->prev_x = x;
		fdf->mouse->prev_y = y;
		ft_draw(fdf);
	}
	else if (fdf->mouse->button == MOUSE_CLICK_MIDDLE)
		ft_move_z(x, y, fdf);
	return (0);
}

int	ft_close_win(void *params)
{
	t_fdf	*fdf;
	int		x;
	int		y;

	fdf = (t_fdf *)params;
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf->camera);
	free(fdf->mouse);
	x = -1;
	while (++x < fdf->map->x)
	{
		y = -1;
		while (++y < fdf->map->y)
			free(fdf->map->array[x][y]);
		free(fdf->map->array[x]);
	}
	free(fdf->map->array);
	free(fdf->map);
	free(fdf->mlx);
	free(fdf);
	exit(0);
}