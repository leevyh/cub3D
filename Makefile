# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 15:35:53 by lkoletzk          #+#    #+#              #
#    Updated: 2023/11/29 15:35:53 by lkoletzk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = srcs/main.c \
		srcs/utils.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = libft/libft.a

MINILIBX_DIR = minilibx-linux
MINILIBX = minilibx-linux/libmlx_Linux.a minilibx-linux/libmlx.a

CC = cc

CFLAGS = -Wall -Wextra -Werror
FLAGS = -lX11 -lXext

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)$(LIBFT) $(MINILIBX)
	@ echo "\033[97;4m🚧 cub3d in progress 🚧\033[0m\n"
	@ $(CC) $(FLAGS) $(CFLAGS) $(OBJ) -o $(NAME) $(MINILIBX)
	@ echo "\033[32;1m✅ CUB3D READY ✅\033[0m\n"

$(LIBFT_DIR)$(LIBFT):
	@ echo "\n\033[97;4m🚧 creating libft 🚧\033[0m\n"
	@ make --no-print-directory -C $(LIBFT_DIR)
	@ echo "\033[32;1m\n★ LIBFT OK ★\033[0m\n"

$(MINILIBX) :
	$(MAKE) -C $(MINILIBX_DIR)

%.o: (SRC)/%.c
	@ mkdir -p $(dir $@)
	@ echo "\n\033[97;4m🚧 compiling $@ file 🚧\033[0m\n"
	@ $(CC) $(CFLAGS) -c $< -o $@
	@ echo "\033[32;1m★ bin OK ★\033[0m\n"

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(MINILIBX)

re: fclean all

.PHONY: all clean fclean re
