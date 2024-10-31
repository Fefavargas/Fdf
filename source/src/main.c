/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:18:47 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/31 19:23:36 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_draw_instructions(t_fdf *env)
{
	mlx_string_put(env->mlx, env->win, 5, 0, 0xFFFFFF,
		"Left Click:   Pan");
	mlx_string_put(env->mlx, env->win, 5, 20, 0xFFFFFF,
		"Right Click:  Rotate x/y");
	mlx_string_put(env->mlx, env->win, 5, 40, 0xFFFFFF,
		"Middle Click: Rotate z");
	if (env->camera->iso)
		mlx_string_put(env->mlx, env->win, 5, 60, 0xFFFFFF,
			"Space:        Toggle projection (Current: Isometric)");
	else
		mlx_string_put(env->mlx, env->win, 5, 60, 0xFFFFFF,
			"Space:        Toggle projection (Current: Parrallel)");
	mlx_string_put(env->mlx, env->win, 5, 80, 0xFFFFFF,
		"R:            Reset");
	mlx_string_put(env->mlx, env->win, 5, 100, 0xFFFFFF,
		"-/+:          Flatten");
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int i;

	i = x;
	while (i)
	{
	pixel = img->data + (y * img->size_line + x * img->bpp / 8);
	*(int *)pixel = color;
		x -= i;
		i--;
	}
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		return (0);
	fdf = inicialize(); 
	inic_map(fdf, argv[1]);
	read_file(fdf);
	init_camera(fdf);
	hook_control(fdf);
	ft_putstr_fd("50-you are here\n", 1);
	ft_draw_instructions(fdf);
	img_pix_put(fdf->img, 1000, 1000, 150);
	//ft_draw(fdf);
	ft_putstr_fd("60-you are here\n", 1);
	mlx_loop(fdf->mlx);
	return (0);
}
