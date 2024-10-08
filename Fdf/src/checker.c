/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:36:41 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/01 20:17:26 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(t_fdf *fdf)
{
	close(fdf->fd);
}

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
	return (-1);
}

int	check_x_y(t_fdf *fdf)
{
	if (!fdf->x || !fdf->y)
	{
		error(fdf);
		return (0);
	}
	return (1);
}

int	check_nbr(char *str)
{
	size_t	j;
	long	nbr;

	j = 0;
	while (str[j])
	{
		if (str[j] == '-')
			j++;
		if (str[j] == '+')
			j++;
		if (ft_isdigit(str[j]))
			j++;
		return (0);
	}
	nbr = ft_atoi(str);
	if (nbr < INT_MIN || nbr > INT_MAX)
		return (0);
	return (1);
}