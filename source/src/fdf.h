/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:20:32 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/13 07:26:14 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <unistd.h> //write()
# include <fcntl.h> // open, close, read, write
# include <stdlib.h> //free
# include <limits.h> //INT_MIN INT_MAX
# include "../mlx/mlx.h" //MiniLibX
# include <math.h> //sin, cos
# include <stdio.h> //perror
# include "setting.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_bresen
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
}	t_bresen;

// typedef struct s_mouse
// {
// 	int	button;
// 	int	x;
// 	int	y;
// 	int	prev_x;
// 	int	prev_y;
// }	t_mouse;

typedef struct s_camera
{
	//int		zoom;
	//float	x_angle;
	//float	y_angle;
	//float	z_angle;
	float	scale;
	int		x_offset;
	int		y_offset;
	float	angle;
	float	z_scale;
}	t_camera;

typedef struct s_img
{
	void	*img;
	char	*data;
	int		size_len;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_map
{
	int	x_max;
	int	y_max;
	int	***array;
	// int	z_min;
	// int	z_max;
}	t_map;

typedef struct s_proj
{
	float	**x_proj;
	float	**y_proj;
	float	x_proj_max;
	float	y_proj_max;
	float	x_proj_min;
	float	y_proj_min;
}	t_proj;

typedef struct s_fdf
{
	int			fd;
	char		*filename;
	t_map		map;
	t_proj		proj;
	void		*mlx;
	void		*win;
	t_img		img;
	t_camera	camera;
}	t_fdf;

//read_file.c
void	parse_map(t_fdf *fdf);
//color.c
int		get_color_code(char *str, char **token_arr, t_fdf *fdf);
void	black_background(t_fdf *fdf);
//error.c
void	check_file(int argc, char **argv);
void	msg_and_exit(char *msg, t_fdf *fdf);
void	perror_and_exit(char *msg, t_fdf *fdf);
void	open_file(t_fdf *fdf);
void	close_file(t_fdf *fdf);
//free.c
void	free_fdf(t_fdf *fdf);
void	free_str_arr(char **array);
//inicialize.c
void	inic_proj_min_max(t_fdf *fdf);
void	inic_fdf(t_fdf *fdf, char *file);
void	inic_map_xy_array(t_fdf *fdf);
void	inic_proj(t_fdf *fdf);
//util.c
int		count_words(char *s);
int		ft_bigger(int x, int y);
int		ft_smaller(int x, int y);
float	ft_bigger_float(float x, float y);
t_point	create_point(int x, int y);
//projection.c
void	project(t_fdf *fdf, int angle);
//hook.c
void	hook_control(t_fdf *fdf);
//draw.c
void	img_pix_put(t_img *img, int x, int y, int color);
void	ft_draw(t_fdf *fdf);

#endif