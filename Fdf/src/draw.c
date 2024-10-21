/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:12:29 by marvin            #+#    #+#             */
/*   Updated: 2024/10/12 21:12:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(int x, int y, int color, t_fdf *fdf)
{
	int	i;

	if (x >= 0 && x <= WINDOW_W && y >= 0 && y < WINDOW_H)
	{
		i = (x * fdf->img->bpp / 8) + (y * fdf->map->x);
		fdf->img->data[i] = color;
		fdf->img->data[++i] = color >> 8;
		fdf->img->data[++i] = color >> 16;
	}
}

void	draw_line(t_fdf *fdf, t_point ini, t_point fin)
{
	int deltax;
	int deltay;
	int error1;
	int error0;
	t_point tmp;

//no original aqui tem um abs para o delta. mas eu considero que estao sempre passando a posição x, y e x+1, y dps x, y e x, y+1
	deltax = fin.x - ini.x;
	deltay = fin.y - ini.y;
	error0 = deltax - deltay;
	tmp = fin;
	while (tmp.x != ini.x || tmp.y != ini.y)
	{
		put_pixel(tmp.x, tmp.y, get_color(), fdf);
		if ((error1 = error0 * 2) > - deltay)
		{
			error0 -= deltay;
			tmp.x += 1;
		}
		if (error1 < deltax)
		{
			error0 += deltax;
			tmp.y += 1;
		}
	}
}


void	ft_draw(t_fdf *fdf)
{
	int x;
	int y;

	ft_bzero(fdf->img->data, WINDOW_H * WINDOW_W * fdf->img->bpp / 8);
	x = 0;
	while (x < fdf->map->x - 1)
	{
		y = 0;
		while (y < fdf->map->y - 1)
		{
			draw_line(fdf, project(x, y, fdf), project(x + 1, y, fdf) );
			draw_line(fdf,  project(x, y, fdf), project(x, y + 1, fdf));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}