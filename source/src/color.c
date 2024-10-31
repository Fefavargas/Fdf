/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:32:38 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/31 15:53:05 by fvargas          ###   ########.fr       */
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

int	get_default_color(int z, t_map *map)
{
	double			percent;
	unsigned int	max;

	max = map->z_max - map->z_min;
	if (max == 0)
		return (0x432371);
	percent = ((double)(z - map->z_min) / max);
	if (percent < 0.2)
		return (0x432371);
	else if (percent < 0.4)
		return (0x714674);
	else if (percent < 0.6)
		return (0x9F6976);
	else if (percent < 0.8)
		return (0xCC8B79);
	else
		return (0xFAAE7B);
}


static int	ft_lerp(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

int	get_color_rgb(int x, t_point ini, t_point fin, float factor)
{
	int		r;
	int		g;
	int		b;
	float	percent;

	percent = ft_abs(x - ini.x) / ft_abs(fin.x - ini.x);
	// if (ini)
	// {
	r = ft_lerp((fin.color >> 16) & 0xFF, (ini.color >> 16) & 0xFF, percent);
	g = ft_lerp((fin.color >> 8) & 0xFF, (ini.color >> 8) & 0xFF, percent);
	b = ft_lerp(fin.color & 0xFF, ini.color & 0xFF, percent);
	// else
	// {
	// 	r = ft_lerp((s.color >> 16) & 0xFF, (e.color >> 16) & 0xFF, percent);
	// 	g = ft_lerp((s.color >> 8) & 0xFF, (e.color >> 8) & 0xFF, percent);
	// 	b = ft_lerp(s.color & 0xFF, e.color & 0xFF, percent);
	// }
	r *= factor;
	g *= factor;
	b *= factor;
	return ((r << 16) | (g << 8) | b);
}
