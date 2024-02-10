# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 16:24:26 by atucci            #+#    #+#              #
#    Updated: 2024/02/09 17:16:34 by lomakinaval      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = ./main.c \
	  ./read_map.c \
	  ./draw_line.c \
	  ./key_hooks.c \
	  ./gradient_colors.c \

OBJS = $(SRC:.c=.o)

HDRS = ./fdf.h

RM = rm -f

CC = cc -Wall -Wextra -Werror

LIBFT = libft/libft.a

PRINTF = printf/libftprintf.a

MLX_FLAG = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit 

MLX_DIR = ./minilibx_macos

GREEN := \033[1;32m
CYAN := \033[1;36m
YELLOW := \033[1;33m
RED := \033[1;31m
RESET := \033[0m

.c.o:
	${CC} -I ${HDRS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@echo "$(CYAN)Building $(NAME)...$(RESET)"
	$(MAKE) -C printf
	$(MAKE) -C libft
	$(MAKE) -C minilibx_macos
	${CC} -o $(NAME) $(OBJS) $(LIBFT) $(PRINTF) -L$(MLX_DIR) -lmlx $(MLX_FLAG)
	@echo "$(GREEN)$(NAME) binary created successfully! $(RESET)"

all: $(NAME)

clean:
	@echo "$(YELLOW)Cleaning up object files...$(RESET)"
	${RM} $(OBJS)
	$(MAKE) -C printf clean
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx_macos clean

fclean: clean
	@echo "$(YELLOW)Cleaning up $(NAME) binary...$(RESET)"
	${RM} $(NAME)
	$(MAKE) -C printf fclean
	$(MAKE) -C libft fclean

download_mlx:
	if [ -e $(MLX_DIR) ]; \
	then \
	echo "MiniLibX's directory detected"; \
	else \
	git clone git@github.com:42Paris/minilibx-linux.git \
	&& mv minilibx-linux mlx; fi

re: fclean all

.PHONY: all clean fclean re

