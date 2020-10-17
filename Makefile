# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/29 19:40:31 by obouykou          #+#    #+#              #
#    Updated: 2020/10/15 10:47:27 by obouykou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIB = libcub3d.a

GAME_MAIN = cub3d.c

FILES = $(wildcard ./srcs/*.c)

HEADER = ./includes/cub3D.h

OBJECT = $(FILES:.c=.o)

FLAGS = -Wextra -Werror -Wall

all: $(NAME)

$(NAME): $(OBJECT) $(HEADER)
	@mv *.o ./srcs
	@ar -rcs $(LIB) $(OBJECT)
	@gcc  $(FLAGS) -I /usr/local/include $(GAME_MAIN) $(LIB) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "\n\033[32m------- Cub3D Game has been created successfully -------\033[0m\n"

bonus: all

%.o:%.c	$(HEADER)									
	@gcc -c $< $(FLAGS) 

clean:
	@rm -rf srcs/*.o $(LIB)
	@echo "\n\033[36mCleaning objects Done!\033[0m\n"

fclean: clean
	@rm -rf $(NAME)

re : fclean all

