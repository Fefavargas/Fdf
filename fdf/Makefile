# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 20:36:48 by fvargas           #+#    #+#              #
#    Updated: 2024/10/28 21:41:27 by fefa             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			fdf
CC = 			cc
CFLAGS =		-Wall -Wextra -Werror -g -lm
LIBFT =			libft/libft.a
MLX =			minilibx-linux/libmlx.a #minilibx-linux/libmlx_Linux.a
HDRS =			src/fdf.h src/setting.h
SRCS =			src/checker.c src/draw.c src/error.c src/hook.c src/inicialize.c \
				src/main.c src/mouse.c src/projection.c src/read_file.c src/util.c

OBJS = 			$(SRCS:.c=.o)

RM = rm -rf

${NAME}: $(OBJS) $(LIBFT) $(MLX)
				 $(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

all: ${NAME}

clean:
	${RM} ${OBJS}
	make clean -C ./libft
	
	
fclean:	clean
		${RM} ${NAME}
	
re: fclean all

$(OBJS): $(HDRS)