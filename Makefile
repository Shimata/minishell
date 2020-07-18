# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/07 23:33:20 by wquinoa           #+#    #+#              #
#    Updated: 2020/07/19 00:29:02 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Source files
SRCS :=			minishell.c	env.c env_paste.c parse_args.c parse_utils.c

#	Utilities
WHT = \033[0m
GRN = \033[32m
RED = \033[31m
WHT1 = \033[0;1m
GRN1 = \033[32;1m
RED1 = \033[31;1m
DRK = \033[2m
MADE_MSG = \r   $(WHT1)Created $(GRN1)
DEL_MSG = \r   $(WHT1)Removed $(DRK)$(RED1)
ERROR_MSG = "\n   $(WHT1)$(DRK)Nothing to $@$(WHT)\n"

#	Variables
NAME = minishell

#	Dirs
BIN = ./obj
S_DIR = ./src
I_DIR = ./include

#	Files
S_FILES = $(addprefix $(S_DIR)/, $(SRCS))
OBJ = $(SRCS:c=o)
BOBJ = $(B_FILES:c=o)

CC = gcc
CF = -Wall -Wextra -Werror -g
.PHONY: all libft bonus clean fclean re

#	Conditionals
ifdef WITH_BONUS
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ)) $(addprefix $(BIN)/, $(BSRCS:c=o))
else
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ))
endif

#	Rules
all: $(NAME)

bonus:
	@$(MAKE) 'WITH_BONUS = true' all

$(NAME): $(S_FILES) | libft
	@gcc $^ ./libft/libft.a -I $(I_DIR) -o $(NAME)
	@echo "$(MADE_MSG)$(NAME)$(WHT)\n"
	@./$(NAME)
ifeq ($(WITH_BONUS),true)
	@echo "	$(WHT1)...added $(GRN1)ft_printf$(WHT)\n"
endif

libft:
	@$(MAKE) -C libft

#	Trash removal rules
clean:
	@$(MAKE) -C libft clean

fclean: clean
	@$(MAKE) -C libft fclean
	@if test -f $(NAME); \
	then rm -rf $(NAME); \
	rm -rf a.out; \
	echo "$(DEL_MSG)$(NAME)$(WHT)\n"; \
	else echo $(ERROR_MSG); \
	fi

re: fclean all
