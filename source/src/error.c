/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:21:26 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/29 22:24:26 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fd(t_fdf *fdf)
{
	int	x;
	int	y;

	if (fdf->filename)
		free(fdf->filename);
	if (fdf->camera)
		free(fdf->camera);
	free(fdf->mouse);
	y = -1;
	while (++y < fdf->map->y)
	{
		x = -1;
		while (++x < fdf->map->x)
			free(fdf->map->array[y][x]);
		free(fdf->map->array[y]);
	}
	free(fdf->map->array);
	free(fdf->map);
	free(fdf->mlx);
	free(fdf);
}

void	error(char *msg)
{
	ft_putstr_fd(msg, 1);
	exit(EXIT_FAILURE);
}
