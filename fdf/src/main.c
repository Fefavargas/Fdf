/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:18:47 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/21 19:12:44 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	read_file(t_fdf *fdf)
{
	char	*str;

	if (!init_map(fdf))
		return (0);
	if (!open_file(fdf))
		return (0);
	while (str = get_next_line(fdf->fd))
	{
		if (!split_mult(str, &fdf))
		{
			get_next_line(-1);
			return (0);
		}
		fdf->map->y++;
	}
	get_next_line(-1);
	close(fdf->fd);
	ft_z_min_max(fdf);
	return (1);
}

int	inicialize(char *str, t_fdf *fdf)
{
	fdf = NULL;
	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		return (0);
	fdf->filename = (char *)ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!fdf->filename)
		return (0);
	ft_strlcpy(fdf->filename, str, ft_strlen(str));
	fdf->map = ft_calloc(sizeof(t_map), 1);
	if (!fdf->map)
		return (0);
	fdf->map->array = 0;
	fdf->map->x = 0;
	fdf->map->y = 0;
	fdf->map->z_max = 0;
	fdf->map->z_min = 0;
	fdf->mouse = (t_mouse *)ft_calloc(sizeof(t_mouse), 1);
	if (!fdf->mouse)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (0);
	if (!inicialize(argv[1], &fdf))
	{
		free_fd(&fdf);
		return (0);
	}
	if (!read_file(&fdf) || !init_mlx(&fdf))
	{
		free_fd(&fdf);
		return (0);
	}
	if (init_camera(&fdf))
	{
		free_fd(&fdf);
		return (0);
	}
	hook_control(&fdf);
	ft_draw(&fdf);
	mlx_loop((&fdf)->mlx);
	return (0);
}
