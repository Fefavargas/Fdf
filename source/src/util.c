/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:06:52 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/11 13:55:23 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_empty(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	return (0);
}

int	count_words(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_empty(s[i]))
			i++;
		if (s[i] && !is_empty(s[i]))
			count++;
		while (s[i] && !is_empty(s[i]))
			i++;
	}
	return (count);
}

int	ft_bigger(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

int	ft_smaller(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

float	ft_bigger_float(float x, float y)
{
	if (x > y)
		return (x);
	return (y);
}

t_point	create_point(int x, int y)
{
	t_point p;

	p.x = x;
	p.y = y;
	return (p);
}