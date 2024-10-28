/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:12:29 by marvin            #+#    #+#             */
/*   Updated: 2024/10/28 21:18:53 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_lerp(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

int	get_color_rgb(int x, t_point ini, t_point fin, float factor)
{
	int r;
	int g;
	int b;
	float	percent;

	percent = ft_abs(x - ini.x) / ft_abs(fin.x - ini.x);
	// if (ini)
	// {
	r = ft_lerp((fin.color >> 16) & 0xFF, (ini.color >> 16) & 0xFF, percent);
	g = ft_lerp((fin.color >> 8) & 0xFF, (ini.color >> 8) & 0xFF, percent);
	b = ft_lerp(fin.color & 0xFF, ini.color & 0xFF, percent);
	// else
	// {
	// 	r = ft_lerp((s.color >> 16) & 0xFF, (e.color >> 16) & 0xFF, percent);
	// 	g = ft_lerp((s.color >> 8) & 0xFF, (e.color >> 8) & 0xFF, percent);
	// 	b = ft_lerp(s.color & 0xFF, e.color & 0xFF, percent);
	// }
	r *= factor;
	g *= factor;
	b *= factor;
	return ((r << 16) | (g << 8) | b);
}

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
	float deltax;
	float deltay;
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
		put_pixel(tmp.x, tmp.y, get_color_rgb(tmp.x, ini, fin ,deltay), fdf);
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
			draw_line(fdf, project(x, y, fdf), project(x + 1, y, fdf));
			draw_line(fdf, project(x, y, fdf), project(x, y + 1, fdf));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
