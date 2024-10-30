/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:21:26 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/30 01:41:48 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_file(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i])
	{
		if (str[i] && str[i] == '.')
		{
			if (ft_strncmp(&str[i], ".fdf", 4))
			{
				return (1);
			}
		}
		i--;
	}
	return (0);
}

void	open_file(t_fdf *fdf)
{
	if (!check_file(fdf->filename))
		error("open file error");
	fdf->fd = open(fdf->filename, O_RDONLY);
	if (fdf->fd == -1)
		error("open file error");
}

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
