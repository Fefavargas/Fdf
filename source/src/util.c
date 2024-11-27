/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:06:52 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/27 12:25:54 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_empty(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	return (0);
}

int	count_words(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_empty(s[i]))
			i++;
		if (s[i] && !is_empty(s[i]))
			count++;
		while (s[i] && !is_empty(s[i]))
			i++;
	}
	return (count);
}

t_point	create_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

void	inic_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		msg_and_exit("Error: mlx inicialize.\n", fdf);
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_W, WINDOW_H, WINDOW_TITLE);
	if (!fdf->win)
		msg_and_exit("Error: window inicialize.\n", fdf);
	fdf->img.img = mlx_new_image(fdf->mlx, WINDOW_W, WINDOW_H);
	if (!fdf->win)
		msg_and_exit("Error: image initializing", fdf);
	fdf->img.data = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp,
			&fdf->img.size_len, &fdf->img.endian);
}
