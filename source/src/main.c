/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:18:47 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/25 16:11:10 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	check_file(argc, argv);
	inic_fdf(&fdf, argv[1]);
	parse_map(&fdf);
	ft_draw(&fdf);
	hook_control(&fdf);
	mlx_loop(fdf.mlx);
}
