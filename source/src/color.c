/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:32:38 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/25 16:14:00 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_digit(char c, int digit_base)
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

int	get_color_code(char *str, char **token_arr, t_fdf *fdf)
{
	int	color;
	int	i;

	if (!ft_strncmp(str, "0x", 2) || !ft_strncmp(str, "0X", 2))
	{
		i = 1;
		color = 0;
		while (str[++i] && !is_empty(str[i]))
		{
			color *= 16;
			color += get_digit(ft_tolower(str[i]), 16);
		}
		if (color >= 0 && color <= 16777215)
			return (color);
	}
	free_str_arr(token_arr);
	msg_and_exit("Invalid color code.\n", fdf);
	return (-1);
}

void	black_background(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WINDOW_H)
	{
		j = -1;
		while (++j < WINDOW_W)
			img_pix_put(&fdf->img, j, i, BLACK);
	}
}

// int	get_default_color(int z, t_map map)
// {
// 	double			percent;
// 	unsigned int	max;

// 	max = map.z_max - map.z_min;
// 	if (max == 0)
// 		return (WIRE_COLOR);
// 	percent = ((double)(z - map.z_min) / max);
// 	if (percent < 0.2)
// 		return (WHITE);
// 	else if (percent < 0.4)
// 		return (YELLOW);
// 	else if (percent < 0.6)
// 		return (GREEN);
// 	else if (percent < 0.8)
// 		return (RED);
// 	else
// 		return (BLUE);
// }

// void	ft_adjust_color(t_fdf *fdf)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < fdf->map.y_max)
// 	{
// 		j = -1;
// 		while (++j < fdf->map.x_max)
// 		{
// 			if (fdf->map.array[j][i][1] == WIRE_COLOR)
// 				fdf->map.array[j][i][1] = 
//get_default_color(fdf->map.array[j][i][0], fdf->map);
// 		}
// 	}
// }
