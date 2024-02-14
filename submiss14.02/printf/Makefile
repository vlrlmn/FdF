# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 12:14:58 by vlomakin          #+#    #+#              #
#    Updated: 2024/02/06 10:54:00 by lomakinaval      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRCS	= ./ft_printf.c \
	   	./print_char.c \
		./print_digit.c \
		./print_integer.c \
		./print_pointer.c \
		./print_str.c \
		./print_unsigned.c \
		./print_hex.c \

OBJS	= $(SRCS:.c=.o)

CC	= cc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
