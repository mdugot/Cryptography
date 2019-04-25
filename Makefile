NAME= ft_ssl
CC= gcc
CFLAGS= -Wall -Werror -Wextra -g
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRC_PATH= ./sources/
SRC= $(call rwildcard, $(SRC_PATH), *.c)
SRC_NAME= $(SRC:$(SRC_PATH)%=%)
INC_PATH= ./includes/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
OBJ_DIR= $(sort $(dir $(OBJ)))
LIB_NAME= libft.a
LIB_ID= ft
LIB_PATH= ./libft/
LIB_INC= ./libft/includes/
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all
all: objdir $(NAME)
	@printf "\n\033[2K[ \033[34m$(NAME) successfully created\033[0m ]\n"

.PHONY: objdir
objdir:
	@mkdir $(OBJ_DIR) 2>/dev/null || echo "" > /dev/null

$(NAME): $(OBJ) $(LIB)
	@$(CC) $(CFLAGS) -o $(NAME) -I$(INC_PATH) -L$(LIB_PATH) -l$(LIB_ID) $(OBJ)
	@printf "\033[2K[ \033[31mcompiling\033[0m ] $< \r"

obj/%.o: sources/%.c
	@$(CC) -I$(INC_PATH) -I$(LIB_INC) $(CFLAGS) -o $@ -c $<
	@printf " \033[2K[ \033[31mcompiling\033[0m ] $< \r"

$(LIB):
	@make -C $(LIB_PATH)

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@printf "[ \033[36mdelete\033[0m ] objects from $(NAME)\n"
	@rm -rf $(OBJ_PATH)
	@printf "[ \033[36mdelete\033[0m ] objects from $(LIB_NAME)\n"
	@make $@ -C $(LIB_PATH)

.PHONY: fclean
fclean: clean
	@printf "[ \033[36mdelete\033[0m ] $(NAME)\n"
	@rm -f $(NAME)
	@make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
