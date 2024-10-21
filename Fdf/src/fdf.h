/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:20:32 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/08 17:09:33 by fvargas          ###   ########.fr       */
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
# include <math.h> //sin, cos
# include "setting.h"

typedef struct s_point
{
	int	x;
	int	y;
	int z;
	int	color;
}t_point;

typedef struct s_mouse
{
	int	button;
	int x;
	int y;
}t_mouse;

typedef struct s_camera
{
	int	zoom;
	double x_angle;
	double y_angle;
	double z_angle;
	double z_height;
	int	x_offset;
	int y_offset;
	int iso;
}t_camera;

typedef	struct s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_len;
	int		endian;
}t_img;

typedef struct s_map
{
	int	x;
	int	y;
	int	***array;
	int z_min;
	int z_max;
}t_map;


typedef struct s_fdf
{
	int			fd;
	char		*filename;
	t_map		*map;
	void		*mlx;
	void		*win;
	t_img		*img;
	t_camera	*camera;
	t_mouse		*mouse;
}t_fdf;

//read_file.c
int		read_file(t_fdf *fdf);
//checker.c
void	error(t_fdf *fdf);
int		check_file(char *array);
//int		check_x_y(t_fdf *fdf);
int		check_nbr(char *str);
//error.c
void	free_fd(t_fdf *fdf);
//inicialize.c
int		inic_map(t_fdf *fdf);
void	init_mlx(t_fdf	*fdf);
//util.c
int		is_empty(char c);
int		count_words(char *s);
int		open_file(t_fdf *fdf);
//projection.c
t_point	project(int x, int y, t_fdf *fdf);

#endif