/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:21:26 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/28 20:16:53 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fd(t_fdf *fdf)
{
	int	x;
	int	y;

	free(fdf->filename); // inside?
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
