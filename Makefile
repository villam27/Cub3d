# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 09:47:26 by lcrimet           #+#    #+#              #
#    Updated: 2023/02/17 18:10:18 by lcrimet          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

VERSION		= 0.0.1

SRCS		= 

HEADERS		= includes \
			  
CCDEFS		= VERSION=\"$(VERSION)\" \
			  NAME=\"$(NAME)\" \

LIB_NAMES	= libmlx \
			  libft \
			  
LIBS		= $(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD		= $(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS	= $(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-I$(lib)/includes/)

CCDEFSFLGS	= $(foreach def,$(CCDEFS),-D $(def))

BUILDDIR	= .build
OBJS		= $(SRCS:%.c=$(BUILDDIR)/%.o) 
DEPS		= $(SRCS:%.c=$(BUILDDIR)/%.d) 
CC			= cc
CCWFLGS		= -Wall -Wextra -Werror #-g -fsanitize=address
CCDBGFLGS	= -DDEBUG -g -fsanitize=address
CCDEPSFLAGS	= -MMD -MP
RM			= rm -Rf
MAKE		= make -C
MKDIR		= mkdir
ECHO		:= echo -e
MLX_FLAGS	= -Llibmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
MLX_CCFLAGS	= #-O3

all : banner libs $(NAME)

$(NAME) : $(LIB_PATHS) $(OBJS)
		$(CC) $(CCWFLGS) $(CCDBGFLGS) $(MLX_FLAGS) -o $(NAME) $(OBJS) $(LIB_LD) $(LIBS)

bonus : $(NAME)

libs :
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib); \
		)

clean : banner
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
		$(CC) $(CCWFLGS) $(CCDEPSFLAGS) $(CCDBGFLGS) $(CCDEFSFLGS) $(MLX_CCFLAGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@

banner :
		
		@$(ECHO) '\x1b[1m\x1b[38;5;6m  _____       _           ___________  '
		@$(ECHO) '\x1b[1m\x1b[38;5;6m /  __ \     | |         |____ |  _  \ '
		@$(ECHO) '\x1b[1m\x1b[38;5;6m | /  \/_   _| |__   ___     / / | | | '
		@$(ECHO) '\x1b[1m\x1b[38;5;6m | |   | | | |  _ \ / _ \    \ \ | | | '
		@$(ECHO) '\x1b[1m\x1b[38;5;6m | \__/\ |_| | |_) |  __/.___/ / |/ /  '
		@$(ECHO) '\x1b[1m\x1b[38;5;6m  \____/\__,_|_.__/ \___|\____/|___/   '
		@$(ECHO) '\x1b[1m\x1b[38;5;6m \x1b[0mversion \x1b[1m$(VERSION)      \x1b[38;5;11m lcrimet & alboudje\x1b[0m'

.PHONY: all clean fclean re bonus libs banner
