# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 16:53:34 by vlomakin          #+#    #+#              #
#    Updated: 2024/02/14 12:09:23 by vlomakin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = ./main.c \
	  ./read_map.c \
	  ./draw_line.c \
	  ./key_hooks.c \
	  ./gradient_colors.c \
	  ./destroy_and_free.c \
	  ./validate_data.c \
	  ./return_error.c \
	  ./utils.c \
	  ./fill_matrix.c

OBJS = $(SRC:.c=.o)

HDRS = ./fdf.h

RM = rm -f

CC = cc -Wall -Wextra -Werror -fsanitize=address

LIBFT = Libft/libft.a

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

re: fclean all

.PHONY: all clean fclean re
