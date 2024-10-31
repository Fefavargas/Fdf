/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:01:14 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/31 15:33:11 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_value(char *str, int y, t_fdf *fdf)
{
	char	**array;
	int		i;
	int		j;

	array = ft_split(str, ' ');
	i = -1;
	while (array[++i])
	{
		fdf->map->array[i][y -1][0] = ft_atoi(array[i]);
		j = 0;
		while (array[i][j] && array[i][j] != ',')
			j++;
		if (array[i][j] == ',')
			fdf->map->array[i][y -1][1] = get_color(&array[i][++j]);
		else
			fdf->map->array[i][y -1][1] = -1;
	}
}

void	get_values_map(t_fdf *fdf)
{
	char	*str;
	int		y;

	open_file(fdf);
	str = get_next_line(fdf->fd);
	y = 0;
	while (str && ++y)
	{
		get_value(str, y, fdf);
		free(str);
		str = get_next_line(fdf->fd);
	}
	get_next_line(-1);
	close(fdf->fd);
}

void	ft_z_min_max(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	fdf->map->z_min = fdf->map->array[0][0][0];
	fdf->map->z_max = fdf->map->array[0][0][0];
	while (++i < fdf->map->y)
	{
		j = -1;
		while (++j < fdf->map->x)
		{
			if (fdf->map->array[j][i][0] < fdf->map->z_min)
				fdf->map->z_min = fdf->map->array[j][i][0];
			if (fdf->map->array[j][i][0] > fdf->map->z_max)
				fdf->map->z_max = fdf->map->array[j][i][0];
		}
	}
}

void	read_file(t_fdf *fdf)
{
	inic_map_xy_array(fdf);
	get_values_map(fdf);
	ft_z_min_max(fdf);
}
