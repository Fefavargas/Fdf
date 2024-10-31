/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:09:47 by marvin            #+#    #+#             */
/*   Updated: 2024/10/31 13:54:28 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_translate(int keycode, t_fdf *fdf)
{
	if (keycode == ARROW_LEFT)
		fdf->camera->x_offset -= 10;
	else if (keycode == ARROW_RIGHT)
		fdf->camera->x_offset += 10;
	else if (keycode == ARROW_DOWN)
		fdf->camera->y_offset += 10;
	else if (keycode == ARROW_UP)
		fdf->camera->y_offset -= 10;
}

static void	ft_mod_height(int keycode, t_fdf *env)
{
	if (keycode == MINUS)
		env->camera->z_height += 0.1;
	else if (keycode == PLUS)
		env->camera->z_height -= 0.1;
	if (env->camera->z_height < 0.1)
		env->camera->z_height = 0.1;
	else if (env->camera->z_height > 10)
		env->camera->z_height = 10;
}

static void	ft_reset(t_fdf *env)
{
	env->camera->x_offset = 0;
	env->camera->y_offset = 0;
	if (env->camera->iso)
	{
		env->camera->x_angle = -0.615472907;
		env->camera->y_angle = -0.523599;
		env->camera->z_angle = 0.615472907;
	}
	else
	{
		env->camera->x_angle = -0.523599;
		env->camera->y_angle = -0.261799;
		env->camera->z_angle = 0;
	}
	env->camera->z_height = 1;
	env->camera->zoom = ft_min(WIDTH / env->map->x / 2,
			HEIGHT / env->map->y / 2);
}

int	ft_key_press(int keycode, void *params)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)params;
	ft_putstr_fd("4010-you are here\n", 1);
	if (keycode == ARROW_DOWN || keycode == ARROW_LEFT || keycode == ARROW_UP
		|| keycode == ARROW_RIGHT)
		ft_translate(keycode, fdf);
	else if (keycode == MINUS || keycode == PLUS)
		ft_mod_height(keycode, fdf);
	else if (keycode == KEY_R)
		ft_reset(fdf);
	else if (keycode == ESCAPE)
		ft_close_win(fdf);
	ft_putstr_fd("4011-you are here\n", 1);
	ft_draw(fdf);
	return (0);
}

void	hook_control(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 0, ft_key_press, fdf);
	mlx_hook(fdf->win, 4, 0, ft_mouse, fdf);
	mlx_hook(fdf->win, 6, 0, ft_mouse_move, fdf);
	mlx_hook(fdf->win, 17, 0, ft_close_win, fdf);
}
