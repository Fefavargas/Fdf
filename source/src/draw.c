/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:12:29 by marvin            #+#    #+#             */
/*   Updated: 2024/10/31 16:25:59 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


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

float	ft_rfpart(float n)
{
	if (n > 0.f)
		return (1.f - (n - (int)n));
	return (1.f - (n - ((int)n + 1.f)));
}

void	draw_line(t_fdf *fdf, t_point s, t_point e)
{
	float	dx;
	float	dy;
	float	tmpy;
	int 	tmpx;
	int		reverse;
	int 	gradient;

	ft_putstr_fd("1-you are here\n", 1);
	if (ft_abs(e.y - s.y) > ft_abs(e.x - s.x))
	{
		ft_swap(&s.x, &s.y);
		ft_swap(&e.x, &e.y);
	}
	if (s.x > e.x)
	{
		ft_swap(&s.x, &e.x);
		ft_swap(&s.y, &e.y);
		reverse = 1;
	}
	dx = e.x - s.x;
	dy = e.y - s.y;
	gradient = dy / dx;
	if (dx == 0.0f)
		gradient = 1.f;
	tmpx = s.x;
	tmpy = s.y;
	while (tmpx <= e.x)
	{
		// if (ft_abs(e.y - s.y) > ft_abs(e.x - s.x))
		// {
		// 	ft_putstr_fd("333\n", 1);
		// 	put_pixel(tmpx, ft_rfpart(tmpy), get_color_rgb(tmpx, s, e, dy), fdf);
		// 	put_pixel(tmpx, ft_rfpart(tmpy), get_color_rgb(tmpx, s, e, dy), fdf);
		// }
		// else
		// {
		ft_putstr_fd("1-you are here\n", 1);
		put_pixel(tmpx, ft_rfpart(tmpy), get_color_rgb(tmpx, s, e, dy), fdf);
		put_pixel(tmpx, ft_rfpart(tmpy), get_color_rgb(tmpx, s, e, dy), fdf);
		printf("x =%d y=%f\n", tmpx, tmpy); 
		tmpy += gradient;
		tmpx++;
	}
	ft_putstr_fd("FIM\n", 1);
}

void	ft_draw(t_fdf *fdf)
{
	int	x;
	int	y;

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
		printf("x = %d", x);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	ft_putstr_fd("509-you are here\n", 1);
}
