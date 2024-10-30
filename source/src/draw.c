/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:12:29 by marvin            #+#    #+#             */
/*   Updated: 2024/10/30 18:57:53 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_lerp(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

int	get_default_color(int z, t_map *map)
{
	double			percent;
	unsigned int	max;

	max = map->z_max - map->z_min;
	if (max == 0)
		return (0x432371);
	percent = ((double)(z - map->z_min) / max);
	if (percent < 0.2)
		return (0x432371);
	else if (percent < 0.4)
		return (0x714674);
	else if (percent < 0.6)
		return (0x9F6976);
	else if (percent < 0.8)
		return (0xCC8B79);
	else
		return (0xFAAE7B);
}

int	get_color_rgb(int x, t_point ini, t_point fin, float factor)
{
	int		r;
	int		g;
	int		b;
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

	if (x >= 0 && x <= WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * fdf->img->bpp / 8) + (y * fdf->img->size_line);
		fdf->img->data[i] = color;
		fdf->img->data[++i] = color >> 8;
		fdf->img->data[++i] = color >> 16;
	}
}

void	draw_line(t_fdf *fdf, t_point s, t_point e)
{
	float	dx;
	float	dy;
	int		error1;
	int		error0;
	t_point	tmp;

	dx = e.x - s.x;
	dy = e.y - s.y;
	error0 = dx - dy;
	tmp = e;
	while (tmp.x != s.x || tmp.y != s.y)
	{
		put_pixel(tmp.x, tmp.y, get_color_rgb(tmp.x, s, e, dy), fdf);
		error1 = error0 * 2;
		if (error1 > -dy)
		{
			error0 -= dy;
			tmp.x += 1;
		}
		if (error1 < dx)
		{
			error0 += dx;
			tmp.y += 1;
		}
	}
}

void	ft_draw(t_fdf *fdf)
{
	int	x;
	int	y;

	ft_putstr_fd("501-you are here\n", 1);
	ft_bzero(fdf->img->data, HEIGHT * WIDTH * fdf->img->bpp / 8);
	x = 0;
	ft_putstr_fd("502-you are here\n", 1);
	while (x < fdf->map->x - 1 && x >= 0)
	{
		y = 0;
		ft_putstr_fd("503-you are here\n", 1);
		while (y < fdf->map->y - 1 && y >= 0)
		{
			draw_line(fdf, project(x, y, fdf), project(x + 1, y, fdf));
			draw_line(fdf, project(x, y, fdf), project(x, y + 1, fdf));
			y += -2 * (fdf->camera->x_angle > 0) + 1;
		}
		x += -2 * (fdf->camera->y_angle > 0) + 1;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
