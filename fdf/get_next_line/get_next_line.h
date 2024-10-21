/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:45:02 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/21 19:16:19 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h> // malloc(), free()
# include <stdint.h> // SIZE_MAX
# include <unistd.h> // read()
# include <stddef.h> // size_t
# include "../libft/libft.h"

char	*get_next_line(int fd);

#endif
