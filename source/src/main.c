/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:18:47 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/31 14:17:25 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		return (0);
	fdf = inicialize(); 
	inic_map(fdf, argv[1]);
	read_file(fdf);
	init_camera(fdf);
	hook_control(fdf);
	ft_putstr_fd("50-you are here\n", 1);
	ft_draw(fdf);
	ft_putstr_fd("60-you are here\n", 1);
	mlx_loop(fdf->mlx);
	return (0);
}
