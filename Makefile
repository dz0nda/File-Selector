# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 18:33:54 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2018/10/07 08:44:52 by dzonda      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean lib

NAME = ft_select

MAKE = make
CC = gcc
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -I ./include/
LDLIBS = -lft -ltermcap
LDFLAGS = -Llibft/
RM = rm -f

SRCS_PATH = ./src/
OBJS_PATH = ./obj/
INCS_PATH = ./include/
LIB_PATH = ./libft/

SRCS_NAME =	\
			select.c \
			select_config.c \
			term.c \
			map.c \
			signal.c \
			print.c \
			key.c \
			key_move.c

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))

NB_FILES = $(words $(SRCS_NAME))

all: $(NAME)

$(NAME): lib $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)
	@echo "\033[1;32m[ $(NAME) ] Compiled\033[0m"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@$(eval CURSOR=$(shell echo $$(($(CURSOR) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURSOR) * 100 / $(NB_FILES)))))
	@if [ $(CURSOR) != 1 ]; then\
		(printf "\e[?25l" && printf "\033[1A");\
		fi # hide cursor & move up except first time
	@echo "\033[93m[ $(NAME) ] Compiling: \033[0m\033[1m[$(PERCENT)%] \033[0m$@                       "
	@printf "\e[?25h" #show cursor

lib:
	@make -C $(LIB_PATH)

clean:
	@$(MAKE) -C $(LIB_PATH) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@rm -rf a.out
	@echo "\033[1;31m[ $(NAME) ] deleted\033[0m"
	@rm -rf obj

re: fclean all



