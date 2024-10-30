/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:18:47 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/30 19:35:53 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (0);
	inicialize(&fdf);
	inic_map(&fdf, argv[1]);
	read_file(&fdf);
	init_camera(&fdf);
	ft_putstr_fd("40-you are here\n", 1);
	//hook_control(&fdf);
	// if (fdf.img->data != 0)
	//  	ft_putstr_fd("It's not NULL", 1);
	//  else
	//  	ft_putstr_fd("It's NULL", 1);
	ft_putstr_fd("41-you are here\n", 1);
	// ft_putstr_fd(fdf.img->data_addr, 1);
	// ft_putstr_fd("addr\n", 1);
	// ft_putnbr_fd(fdf.img->bpp, 1);
	// ft_putstr_fd("bpp\n", 1);
	// ft_putnbr_fd(fdf.img->size_len, 1);
	// ft_putstr_fd("size\n", 1);
	ft_putstr_fd("50-you are here\n", 1);
	//ft_draw(&fdf);
	ft_putstr_fd("60-you are here\n", 1);
	mlx_loop((&fdf)->mlx);
	return (0);
}
