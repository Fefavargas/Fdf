# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 20:36:48 by fvargas           #+#    #+#              #
#    Updated: 2024/11/26 17:42:04 by fvargas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			fdf
CC = 			cc
CFLAGS =		-Wall -Wextra -Werror -g
LIBFT =			libft/libft.a
MLX =			mlx/libmlx.a
HDRS =			src/fdf.h src/setting.h
SRCS =			src/draw.c src/error.c src/hook.c src/inicialize.c \
			src/main.c src/projection.c src/read_file.c src/util.c \
			src/color.c src/free.c

OBJS = 			$(SRCS:.c=.o)

RM = rm -rf
	
${NAME}: $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lm -lX11 -lXext -o $(NAME)

$(MLX): 
	make -C mlx

$(LIBFT):
	make -C libft
	
all: ${NAME} $(MLX)

clean:
	${RM} ${OBJS}
	make clean -C libft
	
fclean:	clean
		${RM} ${NAME}
	
re: fclean all

$(OBJS): $(HDRS)
.PHONY: all clean fclean re


