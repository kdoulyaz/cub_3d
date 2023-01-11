# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 15:41:37 by kdoulyaz          #+#    #+#              #
#    Updated: 2023/01/11 15:33:10 by kdoulyaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

OBJ = $(SRC:.c=.o)

EXE = cub3D

FLAGS = -Wall -Wextra -Werror -O3 -fsanitize=address -g 

SRC = ./src/main.c \
	  ./src/parsing.c \
	  ./src/init.c \
	  ./src/conf.c \
	  ./src/get_next_line.c \
	  ./src/get_next_line_utils.c \
	  ./src/utils.c \
	  ./src/freer.c \
	  ./src/rgb.c \
	  ./src/libft_tools.c \
	  ./src/map.c \
	  ./src/player.c \
	  ./src/utils2.c \
	  ./src/mlx.c \
	  
all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(FLAGS) $(SRC) -lmlx -framework OpenGL -framework AppKit -o $(EXE)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXE)

re: fclean all
