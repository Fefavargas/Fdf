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

static int	get_digit(char c, int digit_base)
{
	int	max_digit;

	if (digit_base <= 10)
		max_digit = digit_base + '0';
	else
		max_digit = digit_base - 11 + 'a';
	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);
}

int	get_color(char *str)
{
	int	color;
	int i;

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
	if (str[size] && str[size + 1] && str[size + 1] == ',')
		fdf->map->array[index][fdf->map->y][1] = get_color(str[size + 2]);
	free(str_nbr);
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
			if (!update_value(fdf, &s[i-count], count, index))
				return (0);
			index++;
		}
		if (!s[i])
			i++;
	}
	return (1);
}

int	read_file(t_fdf *fdf)
{
	char	*str;

	if(!inic_map(fdf))
		return (0);
	if (!open_file(fdf))
		return (0);
	while (str = get_next_line(fdf->fd))
	{
		if (!split_mult(str, &fdf))
		{
			free_fd(fdf);
			return (0);
		}
		fdf->map->y++;
	}
	get_next_line(-1);
	close(fdf->fd);
	return (1);
}
