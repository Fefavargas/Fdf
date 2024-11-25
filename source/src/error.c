/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:21:26 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/13 07:25:03 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_file(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		msg_and_exit("Try again: ./fdf filename.fdf\n", NULL);
	len = ft_strlen(argv[1]);
	while (len >= 0 && argv[1][len] != '.')
		len--;
	if (ft_strncmp(argv[1] + len, ".fdf", 4))
		msg_and_exit("Use file with extension fdf\n", NULL);
}

void	msg_and_exit(char *msg, t_fdf *fdf)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	free_fdf(fdf);
	exit(EXIT_FAILURE);
}

void	perror_and_exit(char *msg, t_fdf *fdf)
{
	perror(msg);
	free_fdf(fdf);
	exit(EXIT_FAILURE);
}

void	open_file(t_fdf *fdf)
{
	fdf->fd = open(fdf->filename, O_RDONLY);
	if (fdf->fd == -1)
		perror_and_exit("open file error\n", fdf);
}

void	close_file(t_fdf *fdf)
{
	int	check;

	check = close(fdf->fd);
	if (check == -1)
		perror_and_exit("close file error\n", fdf);
}
