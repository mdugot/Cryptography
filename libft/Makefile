# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2016/06/08 16:34:08 by mdugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
export ARCHIVE=../libft.a
CC= gcc
CFLAGS= -Wall -Werror -Wextra -g
SRC_NAME= ft_printf.c print.c read.c search.c type.c value.c wprint.c\
		  print_str.c utils.c ft_strf.c ft_put.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= tools.a
LIB_ID= ft
LIB_PATH= ./libft/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	@echo ""
	@ar r -c $(NAME) $(OBJ)
	@make add_to_archive -C $(LIB_PATH)
	@ranlib $(NAME)
	@printf "\n\033[2K[ \033[34m$(NAME) successfully created\033[0m ]\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@$(CC) -I$(INC_PATH) -I$(LIB_PATH) $(CFLAGS) -o $@ -c $<
	@printf "\033[2K[ \033[31mcompiling\033[0m ] $< \r"

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@make $@ -C $(LIB_PATH)

.PHONY: fclean
fclean: clean
	@printf "[ \033[36mdelete\033[0m ] $(NAME)\n"
	@rm -f $(NAME)

.PHONY: re
re: fclean all
