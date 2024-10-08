/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:01:14 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/08 15:19:40 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../get_next_line/get_next_line.h"

int	update_value(int *z, char *str, int size, int index)
{
	char	*str_nbr;

	str_nbr = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!str_nbr)
		return (0);
	ft_strlcpy(str_nbr, str, size);
	if (!check_nbr(str_nbr))
	{
		free(str_nbr);
		return (0);
	}
	z[index] = ft_atoi(str_nbr);
	free(str_nbr);
	return (1);
}

int	split_mult(char *s, int *z)
{
	int		i;
	int		index;
	int		count;
	int		nbr;
	char	*str_nbr;

	i = 0;
	index = 0;
	while (s[i])
	{
		count = 0;
		while (s[i] && is_empty(s[i]))
			i++;
		while (s[i] && !is_empty(s[i]))
			count++;
		if (count)
		{
			if (!update_value(z, &s[i], count, index))
				return (0);
			index++;
		}
		if (!s[i])
			i++;
	}
	return (1);
}

int	read_file_get_xy(t_fdf *fdf)
{
	int		y;
	int		x;
	char	*str;

	while ((str = get_next_line(fdf->fd)))
	{
		fdf->y++;
		x = count_words(str);
		if (fdf->x == 0)
			fdf->x = x;
		else if (fdf->x != x)
		{
			error(fdf);
			return (0);
		}
		free(str);
	}
	get_next_line(-1);
	close(fdf->fd);
	return (check_x_y(fdf));
}

int	read_file_get_z(t_fdf *fdf)
{
	int		count_y;
	int		count_x;
	char	*str;

	count_y = 0;
	fdf->z = (int **)ft_calloc(sizeof(int *), (fdf->y));
	if (fdf->z)
		return (0);
	fdf->fd = open(fdf->filename, O_RDONLY);
	if (fdf->fd == -1)
		return (0);
	while ((str = get_next_line(fdf->fd)))
	{
		fdf->z[count_y] = (int *)ft_calloc(sizeof(int), fdf->x);
		if (!fdf->z[count_y])
			return (0);
		if (!split_mult(str, (fdf->z[count_y])))
		{
			free_fd(fdf);
			return (0);
		}
		count_y++;
	}
	get_next_line(-1);
	close(fdf->fd);
	return (1);
}
