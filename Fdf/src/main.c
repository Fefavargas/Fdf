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

int	open_file(t_fdf *fdf)
{
	int	fd;
	int	i;

	if (!check_file(fdf->filename))
		return (0);
	if ((fdf->fd = open(fdf->filename, O_RDONLY)) == -1)
		return (0);
	return (1);
}

void	inicialize(char *str, t_fdf *fdf)
{
	fdf->filename = (char *)ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!fdf->filename)
	{
		fdf = NULL;
		return ;
	}
	ft_strlcpy(fdf->filename, str, ft_strlen(str));
	fdf->z = 0;
}

void	init_mlx(t_fdf	*fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return ;
	fdf->window = mlx_new_window(fdf->mlx, WINDOW_W, WINDOW_H, WINDOW_TITLE);
	if (!fdf->window)
		return ;
	fdf->img.img = mlx_new_image(fdf->mlx,WINDOW_W, WINDOW_H);
	fdf->img.data = mlx_get_data_addr( fdf->img.img, &fdf->img.bpp, &fdf->img.size_len, 
					&fdf->img.endian);
}

#include <stdio.h>
int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (0);
	inicialize(argv[1], &fdf);
	printf("%s", fdf.filename);
	if (open_file(&fdf))
		return (0);
	if (read_file_get_xy(&fdf))
		return (0);
	if (read_file_get_z(&fdf))
		return (0);
	return (0);
}
