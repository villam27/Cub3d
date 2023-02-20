# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 13:00:14 by lcrimet           #+#    #+#              #
#    Updated: 2023/02/15 11:22:02 by lcrimet          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY:		all clean fclean re

SRCS	=	ft_isalpha.c \
			ft_isdigit.c \
			ft_memset.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_strdup.c \
			ft_calloc.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_split_2.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_itoa_ul.c \
			ft_dec2hex_ul.c \
			ft_dec2hex_u.c \
			ft_putnbr_u.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_printf.c \
			ft_printf2.c \
			ft_putnbr.c \
			ft_rverse_str.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_atoui_base.c \
			ft_strcpy.c \
			ft_strcat.c


OBJS	= ${SRCS:.c=.o}

INCL	= includes

NAME	= libft.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address -g

%.o:		%.c includes/libft.h Makefile
			${CC} ${CFLAGS} -I $(INCL) -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJSB}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
