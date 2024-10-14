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
			draw_line(fdf, x , y, x + 1, y);
			draw_line(fdf, x , y, x, y + 1);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window();
}

void	draw_line()
{
	
}
