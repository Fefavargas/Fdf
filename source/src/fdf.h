/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:20:32 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/30 01:42:10 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <unistd.h> //write()
# include <fcntl.h> // open, close, read, write
# include <stdlib.h> //free
# include <limits.h> //INT_MIN INT_MAX
# include "../minilibx-linux/mlx.h" //MiniLibX
# include "../minilibx-linux/mlx_int.h" //MiniLibX
# include <math.h> //sin, cos
# include "setting.h"

//lines -> height -> y
// width -> x

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_mouse
{
	int	button;
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
}	t_mouse;

typedef struct s_camera
{
	int		zoom;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	double	z_height;
	int		x_offset;
	int		y_offset;
	int		iso;
}	t_camera;

typedef struct s_image
{
	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_len;
	int		endian;
}	t_image;

typedef struct s_map
{
	int	x;
	int	y;
	int	***array;
	int	z_min;
	int	z_max;
}	t_map;

typedef struct s_fdf
{
	int			fd;
	char		*filename;
	t_map		*map;
	void		*mlx;
	void		*win;
	t_image		*img;
	t_camera	*camera;
	t_mouse		*mouse;
}	t_fdf;

//read_file.c
void	read_file(t_fdf *fdf);
//error.c
void	open_file(t_fdf *fdf);
void	free_fd(t_fdf *fdf);
void	error(char *msg);
//inicialize.c
void	inic_map_xy_array(t_fdf *fdf);
void	init_camera(t_fdf *fdf);
void	inicialize(t_fdf *fdf);
void	inic_map(t_fdf *fdf, char *filename);
//util.c
int		is_empty(char c);
int		count_words(char *s);
int		get_digit(char c, int digit_base);
int		ft_abs(int a);
int		ft_min(int a, int b);
//projection.c
t_point	project(int x, int y, t_fdf *fdf);
//hook.c
void	hook_control(t_fdf *fdf);
//draw.c
void	ft_draw(t_fdf *fdf);
int		get_default_color(int z, t_map *map);
//mouse.c
int		ft_mouse_move(int x, int y, void *params);
int		ft_mouse(int buttom, int x, int y, void *params);
int		ft_close_win(void *params);

#endif