# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 09:47:26 by lcrimet           #+#    #+#              #
#    Updated: 2023/02/17 15:40:17 by lcrimet          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME		= ilx.out

VERSION		= 0.0.1

SRCS		= srcs/main.c \
			  srcs/window/window.c \
			  srcs/shapes/ilx_circle.c \
			  srcs/shapes/ilx_line.c \
			  srcs/shapes/ilx_rect.c \
			  srcs/shapes/ilx_point.c \
			  srcs/gui/gui.c \
			  srcs/gui/button.c \
			   srcs/gui/button_utils.c \
			  srcs/textures/ilx_texture.c \

HEADERS		= includes \
			  
CCDEFS		= VERSION=\"$(VERSION)\" \

LIB_NAMES	= libmlx \
			  libft \
			  
LIBS		= $(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD		= $(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS	= $(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-I$(lib)/includes/)

BUILDDIR	= .build
OBJS		= $(SRCS:%.c=$(BUILDDIR)/%.o) 
DEPS		= $(SRCS:%.c=$(BUILDDIR)/%.d) 
CC			= cc
CCWFLGS		= -Wall -Wextra -Werror #-g -fsanitize=address
CCDBGFLGS	= -DDEBUG
CCDEPSFLAGS	= -MMD -MP
RM			= rm -Rf
MAKE		= make -C
MKDIR		= mkdir
ECHO		:= echo -e
MLX_FLAGS	= -Llibmlx -lmlx_Linux -L/usr/lib -Ilibmlx -lXext -lX11 -lm -lz
MLX_CCFLAGS	= -Ilibmlx #-O3

all : libs $(NAME)

$(NAME) : $(LIB_PATHS) $(OBJS)
		$(CC) -o $(NAME) $(CCWFLAGS) $(OBJS) $(MLX_FLAGS) $(LIB_PATHS)

bonus : $(NAME)

libs :
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib); \
		)

clean :
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib) clean; \
		)
		-$(RM) $(BUILDDIR)

fclean : clean
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib) fclean; \
		)
		-$(RM) $(NAME)

re : fclean all

-include $(DEPS)

$(BUILDDIR)/%.o : %.c Makefile $(LIB_PATHS)
		@mkdir -p $(@D)
		$(CC) $(CCWFLAGS) $(CCDEPSFLAGS) $(MLX_CCFLAGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@

.PHONY: all clean fclean re bonus libs
