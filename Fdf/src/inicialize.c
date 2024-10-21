/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:02:48 by marvin            #+#    #+#             */
/*   Updated: 2024/10/10 13:02:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int inic_array(t_fdf *fdf)
{
	int	i;

	fdf->map->array = (int ***)ft_calloc(sizeof(int **), fdf->map->x);
	if (!fdf->map->array)
		return (0);
	i = 0;
	while (i < fdf->map->x)
	{
		fdf->map->array[i] = (int **)ft_calloc(sizeof(int *), 2);
		if (!fdf->map->array[i])
			return (0);
		i++;
	}
	return (1);
}

int	inic_map(t_fdf *fdf)
{
	int		x;
	int		y;
	char	*str;

	if (!open_file(fdf))
		return (0);
	while (str = get_next_line(fdf->fd))
	{
		x = count_words(str);
		if (fdf->map->x == 0)
			fdf->map->x = x;
		else if (fdf->map->x != x)
			return (0);
		y++;
	}
	get_next_line(-1);
	close(fdf->fd);
	fdf->map->y = y;
	return (inic_array(fdf));
}

int	init_mlx(t_fdf	*fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (0);
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_W, WINDOW_H, WINDOW_TITLE);
	if (!fdf->win)
		return (0);
	fdf->img->img = mlx_new_image(fdf->mlx,WINDOW_W, WINDOW_H);
	fdf->img->data = mlx_get_data_addr( fdf->img->img, &fdf->img->bpp, &fdf->img->size_len, 
					&fdf->img->endian);
	return (1);
}

