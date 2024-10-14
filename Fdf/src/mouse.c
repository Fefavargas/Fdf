/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:17:29 by marvin            #+#    #+#             */
/*   Updated: 2024/10/13 13:17:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_zoom(int buttom, t_fdf *fdf)
{
	if (buttom == MOUSE_WHEEL_UP)
		fdf->camera->zoom += 2;
	else if (buttom == MOUSE_WHEEL_DOWN)
		fdf->camera->zoom -= 2;
	if (fdf->camera->zoom < 1)
		fdf->camera->zoom = 1;
	ft_draw(fdf);
}

void	ft_mouse(int buttom, int x, int y, t_fdf *fdf)
{
	if (buttom == MOUSE_WHEEL_UP || buttom == MOUSE_WHEEL_DOWN)
		return (ft_zoom(buttom, fdf));
	else if (buttom == MOUSE_CLICK_LEFT || buttom == MOUSE_CLICK_RIGHT 
				|| buttom == MOUSE_CLICK_MIDDLE)
	{
		fdf->mouse->button = buttom;
		fdf->mouse->x = x;
		fdf->mouse->y = y;
	}
}