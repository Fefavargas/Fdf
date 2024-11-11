/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:12:29 by marvin            #+#    #+#             */
/*   Updated: 2024/11/11 13:42:12 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_bresenham(t_bresenham *bresen, t_fdf *fdf, t_point s, t_point e)
{
	bresen->x0 = (int)fdf->proj.x_proj[s.y][s.x];
	bresen->y0 = (int)fdf->proj.y_proj[s.y][s.x];
	bresen->x1 = (int)fdf->proj.x_proj[e.y][e.x];
	bresen->y1 = (int)fdf->proj.y_proj[e.y][e.x];
	bresen->dx = ft_bigger(bresen->x0 - bresen->x1, bresen->x1 - bresen->x0);
	bresen->dy = ft_bigger(bresen->y0 - bresen->y1, bresen->y1 - bresen->y0);
	bresen->sx = -1;
	if (bresen->x0 < bresen->x1)
		bresen->sx = 1;
	bresen->sy = -1;
	if (bresen->y0 < bresen->y1)
		bresen->sy = 1;
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data + (y * img->size_len + x * img->bpp / 8);
	*(int *)pixel = color;
}

static void	draw_line(t_fdf *fdf, int row, int col, t_bresenham bresen)
{
	int			err;
	int			e2;

	err = bresen.dx - bresen.dy;
	while (bresen.x0 != bresen.x1 || bresen.y0 != bresen.y1)
	{
		img_pix_put(&fdf->img, bresen.x0, bresen.y0, fdf->map.array[row][col][1]);
		e2 = 2 * err;
		if (e2 > -bresen.dy)
		{
			err -= bresen.dy;
			bresen.x0 += bresen.sx;
		}
		if (e2 < bresen.dx)
		{
			err += bresen.dx;
			bresen.y0 += bresen.sy;
		}
	}
}

void	ft_draw(t_fdf *fdf)
{
	t_bresenham	bresen;
	t_point		s;
	t_point		e;

	project(fdf, fdf->camera.angle);
	s.y = -1;
	while (++s.y < fdf->map.y_max)
	{
		s.x = -1;
		while (++s.x < fdf->map.x_max)
		{
			if (s.x < (fdf->map.x_max - 1))
			{
				e = create_point(s.x + 1, s.y);
				init_bresenham(&bresen, fdf, s, e);
				draw_line(fdf, s.y, s.x, bresen);
			}
			if (s.y < (fdf->map.y_max -1))
			{
				e = create_point(s.x, s.y + 1);
				init_bresenham(&bresen, fdf, s, e);
				draw_line(fdf, s.y, s.x, bresen);
			}
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
