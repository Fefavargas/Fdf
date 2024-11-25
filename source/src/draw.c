/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:12:29 by marvin            #+#    #+#             */
/*   Updated: 2024/11/25 16:20:33 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_bresenham(t_bresen *bresen, t_fdf *fdf, t_point s, t_point e)
{
	bresen->x0 = (int)fdf->proj.x_proj[s.y][s.x];
	bresen->y0 = (int)fdf->proj.y_proj[s.y][s.x];
	bresen->x1 = (int)fdf->proj.x_proj[e.y][e.x];
	bresen->y1 = (int)fdf->proj.y_proj[e.y][e.x];
	bresen->dx = fmax(bresen->x0 - bresen->x1, bresen->x1 - bresen->x0);
	bresen->dy = fmax(bresen->y0 - bresen->y1, bresen->y1 - bresen->y0);
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

static void	draw_line(t_fdf *fdf, int row, int col, t_bresen bresen)
{
	int	err;
	int	e2;
	int	color;	

	err = bresen.dx - bresen.dy;
	while (bresen.x0 != bresen.x1 || bresen.y0 != bresen.y1)
	{
		color = fdf->map.array[row][col][1];
		img_pix_put(&fdf->img, bresen.x0, bresen.y0, color);
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

void	bresen_and_draw_line(t_fdf *fdf, t_point s, t_point e, t_bresen *b)
{
	init_bresenham(b, fdf, s, e);
	draw_line(fdf, s.y, s.x, *b);
}

void	ft_draw(t_fdf *fdf)
{
	t_bresen	bresen;
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
				bresen_and_draw_line(fdf, s, e, &bresen);
			}
			if (s.y < (fdf->map.y_max -1))
			{
				e = create_point(s.x, s.y + 1);
				bresen_and_draw_line(fdf, s, e, &bresen);
			}
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
