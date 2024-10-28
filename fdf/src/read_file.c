/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:01:14 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/28 21:11:27 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(t_fdf *fdf)
{
	if (!check_file(fdf->filename))
		return (0);
	if ((fdf->fd = open(fdf->filename, O_RDONLY)) == -1)
		return (0);
	return (1);
}

void	ft_z_min_max(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	fdf->map->z_min = fdf->map->array[0][0][0];
	fdf->map->z_max = fdf->map->array[0][0][0];
	while (i < fdf->map->y)
	{
		j = 0;
		while (j < fdf->map->x)
		{
			if (fdf->map->array[j][i][0] < fdf->map->z_min)
				fdf->map->z_min = fdf->map->array[j][i][0];
			if (fdf->map->array[j][i][0] > fdf->map->z_max)
				fdf->map->z_max = fdf->map->array[j][i][0];
			j++;
		}
	}
}

int	get_color(char *str)
{
	int	color;
	int	i;

	if (!ft_strncmp(str, "0x", 2) || !ft_strncmp(str, "0X", 2))
	{
		i = 2;
		color = 0;
		while (str[i])
		{
			color *= 16;
			color += get_digit(str[i], 16);
			i++;
		}
		if (color >= 0 && color <= 16777215)
			return (color);
	}
	return (-1);
}

int	update_value(t_fdf *fdf, char *str, int size, int index)
{
	char	*str_nbr;
	int		color;

	str_nbr = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!str_nbr)
		return (0);
	ft_strlcpy(str_nbr, str, size);
	if (!check_nbr(str_nbr))
	{
		free(str_nbr);
		return (0);
	}
	fdf->map->array[index][fdf->map->y][0] = ft_atoi(str_nbr);
	free(str_nbr);
	if (str[size] && str[size + 1] && str[size + 1] == ',')
	{
		color = get_color(&str[size + 2]);
		if (color == -1)
			return (0);
		fdf->map->array[index][fdf->map->y][1] = color;
	}
	return (1);
}

int	split_mult(char *s, t_fdf *fdf)
{
	int		i;
	int		index;
	int		count;

	i = 0;
	index = 0;
	while (s[i])
	{
		count = 0;
		while (s[i] && is_empty(s[i]))
			i++;
		while (s[i] && !is_empty(s[i++]))
			count++;
		if (count)
		{
			if (!update_value(fdf, &s[i - count], count, index))
				return (0);
			index++;
		}
		if (!s[i])
			i++;
	}
	return (1);
}