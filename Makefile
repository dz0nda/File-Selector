# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/02/01 13:46:52 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2018/06/26 01:56:41 by dzonda      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean

NAME = ft_select

MAKE = make
CC = gcc
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -I./
LDLIBS = -lft -ltermcap
LDFLAGS = -Llibft/
RM = rm -f

SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
INCS_PATH = ./includes/
LIB_PATH = ./libft/

SRCS_NAME =	\
			ft_putchar.c \
			ft_putstr_fd.c \
			ft_strdel.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_select.c \
			ft_select_config.c \
			ft_term.c \
			ft_signal.c \
			ft_print.c \
			ft_keys.c \
			ft_keys_tools.c

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIB_PATH)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)
	@echo "\033[1;32m[ $(NAME) ] Compiled\033[0m"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@$(MAKE) -C $(LIB_PATH) clean
	@$(RM) $(OBJS)
	@echo "\033[1;31mAll .o deleted\033[0m"

fclean: clean
	@$(MAKE) -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@echo "\033[1;31m[ $(NAME) ] deleted\033[0m"

re: fclean all
