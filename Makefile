# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/02/01 13:46:52 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2018/07/19 05:56:20 by dzonda      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean lib

NAME = ft_select

MAKE = make
CC = gcc
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -I./include -I./libft/include
LDLIBS = -ltermcap -lft

LDFLAGS = -Llibft/
RM = rm -f

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/
LIB_PATH = ./libft/

SRC_NAME =	\
			select.c \
			select_config.c \
			term.c \
			map.c \
			signal.c \
			print.c \
			key.c \
			key_move.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@echo "\033[1m[ $@ ] Compiled\033[0m"
	@echo "\033[2A"
	@echo "\033[K"
	@echo "\033[2A"

$(NAME): $(OBJS) $(lib)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)  $(OBJ) -o $(NAME) 
	@echo "\033[1;32m[ $(NAME) ] Compiled\033[0m"

lib:
	@make -C $(LIB_PATH)

clean:
	@$(MAKE) -C $(LIB_PATH) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@echo "\033[1;31m[ $(NAME) ] deleted\033[0m"

re: fclean all
