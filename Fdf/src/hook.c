/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:09:47 by marvin            #+#    #+#             */
/*   Updated: 2024/10/13 13:09:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hook_control(t_fdf *fdf)
{
	/*mlx_hook(fdf->win, 2, 0, ft_key_press, fdf);
	mlx_hook(fdf->win, 4, 0, ft_mouse_down, fdf);
	mlx_hook(fdf->win, 5, 0, ft_mouse_up, fdf);
	mlx_hook(fdf->win, 6, 0, ft_mouse_move, fdf);
	mlx_hook(fdf->win, 17, 0, ft_close_win, fdf);*/
}

int	handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		free_fd(fdf);
	return (0);
}

/*window destruction, */
int	handle_x(t_fdf *fdf)
{
	free_fd(fdf);
	return (0);
}

