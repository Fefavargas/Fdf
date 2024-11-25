/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:09:47 by marvin            #+#    #+#             */
/*   Updated: 2024/11/25 16:42:05 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_x(t_fdf	*fdf)
{
	free_fdf(fdf);
	exit(EXIT_SUCCESS);
	return (0);
}

void	key_up_down(int keycode, t_fdf *fdf)
{
	if (keycode == XK_UP)
		fdf->camera.z_scale += 0.02;
	if (keycode == XK_DOWN)
		fdf->camera.z_scale -= 0.02;
}

int	handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == XK_ESCAPE)
		handle_x(fdf);
	if (keycode == XK_UP || keycode == XK_DOWN)
		key_up_down(keycode, fdf);
	ft_draw(fdf);
	return (0);
}

void	hook_control(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, &handle_keypress, fdf);
	mlx_hook(fdf->win, DESTROY_NOTIFY, 0, &handle_x, fdf);
}

// void	key_left_right(int keycode, t_fdf *fdf)
// {
// 	if (keycode == XK_LEFT)
// 	{
// 		fdf->camera.angle += 10;
// 		if (fdf->camera.angle >= 360)
// 			fdf->camera.angle = 0;
// 	}
// 	if (keycode == XK_RIGHT)
// 	{
// 		fdf->camera.angle -= 10;
// 		if (fdf->camera.angle <= 0)
// 			fdf->camera.angle = 360;
// 	}
// }
