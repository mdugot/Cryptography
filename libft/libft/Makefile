# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 14:09:58 by mdugot            #+#    #+#              #
#    Updated: 2016/06/13 17:26:21 by mdugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -c -g
SOURCE=ft_strlen.c ft_memset.c ft_strdup.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
	   ft_memmove.c ft_memchr.c ft_memcmp.c ft_strcpy.c ft_strncpy.c \
	   ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	   ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c \
	   ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_tolower.c ft_toupper.c ft_memalloc.c ft_memdel.c ft_strnew.c \
	   ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
	   ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
	   ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c ft_putchar.c ft_putstr.c ft_putendl.c \
	   ft_putnbr.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	   ft_lstiter.c ft_lstmap.c ft_lstfind.c ft_lstadd_end.c ft_lstadd_after.c \
	   ft_lstadd_before.c ft_lstbefore.c ft_lstdelin.c ft_lstsize.c \
	   ft_lstsort.c ft_lstadd_sorted.c ft_lstsplit.c nbrcmp.c ft_lstmaxsize.c \
	   ft_deltab.c get_next_line.c ft_itoa_base.c significant_bit.c \
	   ft_putwchar.c ft_ftoa.c ft_isin.c ft_sorttab.c ft_readstr.c ft_random.c \
	   ft_isint.c ft_explode.c ft_replace.c ft_implode.c my_fork.c ft_putwstr.c\
	   ft_strsplit_max.c \
	   ft_create_square.c			\
	   ft_inc_tab.c					\
	   ft_realloc_tab.c				\
	   ft_tab_size.c				\
	   ft_freetab.c					\
	   ft_print_rep.c				\
	   get_next_line.c				\
	   ft_strtrim_w.c				\
	   ft_strdup_tab.c				\
	   ft_implode_tab.c				\
	   ft_index_fmatch.c			\
	   ft_index_lmatch.c			\
	   ft_index_nmatch.c			\
	   ft_cut_cur_word.c			\
	   ft_split_index.c				\
	   ft_trace.c					\
	   ft_nbrtrace.c				\
	   ft_del_cur_word.c			\
	   ft_replace_in_str.c			\
	   ft_str_renew.c

OBJECT= $(SOURCE:.c=.o)
NAME=tools.a
INCLUDE=../includes/

.PHONY: all
all: $(NAME)

.PHONY: add_to_archive
add_to_archive: $(OBJECT)
	@ar r $(ARCHIVE) $(OBJECT)
	@printf "\n\033[2K[ \033[33madd tools object to the archive\033[0m ] \r"

$(NAME): $(OBJECT)
	@ar r $(NAME) $(OBJECT) 
	@ranlib $(NAME)
	@printf "\n\033[2K[ \033[34m$(NAME) successfully created\033[0m ]\n"
	
%.o: %.c
	@$(CC) -I $(INCLUDE) $(CFLAGS) $<
	@printf "\033[2K[ \033[31mcompiling\033[0m ] $< \r"

.PHONY: clean
clean:
	@rm -f $(OBJECT)

.PHONY: fclean
fclean: clean
	@printf "[ \033[36mdelete\033[0m ] $(NAME)\n"
	@rm -f $(NAME)

.PHONY: re
re: fclean all
