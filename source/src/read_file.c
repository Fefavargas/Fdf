/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:01:14 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/26 18:32:07 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "fdf.h"

static	void	get_value(char *str, t_fdf *fdf, int y)
{
	int		x;
	char	**token_arr;
	char	*color_str;
	int		color;

	x = -1;
	token_arr = ft_split(str, ' ');
	if (!token_arr)
		perror_and_exit("Error: ft_split() ", fdf);
	while (++x < fdf->map.x_max)
	{
		fdf->map.array[y][x][0] = ft_atoi(token_arr[x]);
		color_str = ft_strchr(token_arr[x], ',');
		if (color_str)
		{
			color = get_color_code(color_str + 1, token_arr, fdf);
			fdf->map.array[y][x][1] = color;
		}
	}
	free_str_arr(token_arr);
}

void	get_values_map(t_fdf *fdf)
{
	int		y;
	char	*str;

	y = 0;
	open_file(fdf);
	str = get_next_line(fdf->fd);
	while (str)
	{
		get_value(str, fdf, y);
		free(str);
		str = get_next_line(fdf->fd);
		y++;
	}
	close_file(fdf);
}

void	parse_map(t_fdf *fdf)
{
	inic_map_xy_array(fdf);
	get_values_map(fdf);
	inic_proj(fdf);
}

// void	ft_z_min_max(t_fdf *fdf)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	fdf->map.z_min = fdf->map.array[0][0][0];
// 	fdf->map.z_max = fdf->map.array[0][0][0];
// 	while (++i < fdf->map.y_max)
// 	{
// 		j = -1;
// 		while (++j < fdf->map.x_max)
// 		{
// 			if (fdf->map.array[j][i][0] < fdf->map.z_min)
// 				fdf->map.z_min = fdf->map.array[j][i][0];
// 			if (fdf->map.array[j][i][0] > fdf->map.z_max)
// 				fdf->map.z_max = fdf->map.array[j][i][0];
// 		}
// 	}
// }