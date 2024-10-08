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
# include "setting.h"

typedef	struct s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_len;
	int		endian;
}t_img;

typedef struct s_fdf
{
	int		fd;
	char	*filename;
	int		x;
	int		y;
	int		**z;
	void	*mlx;
	void	*window;
	t_img	img;
}t_fdf;

//read_file.c
int		read_file_get_xy(t_fdf *fdf);
int		read_file_get_z(t_fdf *fdf);
//checker.c
void	error(t_fdf *fdf);
int		check_file(char *array);
int		check_x_y(t_fdf *fdf);
int		check_nbr(char *str);
//error.c
void	free_fd(t_fdf *fdf);
//util.c
int		is_empty(char c);
int		count_words(char *s);

#endif