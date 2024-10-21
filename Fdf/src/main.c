/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:18:47 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/08 17:11:15 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	inicialize(char *str, t_fdf *fdf)
{
	fdf->filename = (char *)ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!fdf->filename)
	{
		fdf = NULL;
		return ;
	}
	ft_strlcpy(fdf->filename, str, ft_strlen(str));
	fdf->map = ft_calloc(sizeof(t_map), 1);
	fdf->map->y = 0;
}

#include <stdio.h>
int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (0);
	inicialize(argv[1], &fdf);
	if (!read_file(&fdf))
		return (0);
	init_mlx(fdf);
	return (0);
}
