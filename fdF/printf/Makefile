# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 12:14:58 by vlomakin          #+#    #+#              #
#    Updated: 2023/08/03 13:03:45 by lomakinaval      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRCS	= ./srcs/ft_printf.c \
	   	./srcs/print_char.c \
		./srcs/print_digit.c \
		./srcs/print_integer.c \
		./srcs/print_pointer.c \
		./srcs/print_str.c \
		./srcs/print_unsigned.c \
		./srcs/print_hex.c \

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
