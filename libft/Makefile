# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zfeng <zfeng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/22 14:48:56 by zfeng             #+#    #+#              #
#    Updated: 2018/05/22 22:39:00 by ysibous          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

# directories
SRC_DIR := ./src/
INC_DIR := ./include/

# compiler and flags
CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

# files
FT_BTREE	:=	ft_btree_apply_inorder ft_btree_apply_preorder ft_btreenew \
				ft_btree_apply_postorder

FT_CHAR		:=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint \
				ft_isspace ft_tolower ft_toupper

FT_CONV		:=	ft_atoi ft_itoa ft_itoa_base

FT_LST		:=	ft_lstadd ft_lstaddtoend ft_lstdel ft_lstdelone ft_lstiter \
				ft_lstmap ft_lstnew ft_lstsize

FT_MEM		:=	ft_bzero ft_memalloc ft_memccpy ft_memchr ft_memcmp ft_memcpy \
				ft_memdel ft_memmove ft_memset

FT_PUT		:=	ft_putchar ft_putchar_fd ft_putendl ft_putendl_fd \
				ft_putnbr ft_putnbr_fd ft_putnstr ft_putnwstr ft_putstr \
				ft_putstr_fd ft_putwchar ft_putwstr ft_puterror

FT_STR		:=	ft_strcat ft_strchr ft_strclr ft_strcmp ft_strcpy ft_strdel \
				ft_strdup ft_strequ ft_striter ft_striteri ft_strjoin \
				ft_strlcat ft_strlen ft_strmap ft_strmapi ft_strncat \
				ft_strncmp ft_strncpy ft_strndup ft_strnequ ft_strnew \
				ft_strnstr ft_strrchr ft_strrev ft_strsplit ft_strstr \
				ft_strsub ft_strtrim ft_wstrlen

GNL			:=	get_next_line

FT_PRINTF	:=	dflags uflags helpers parse_fields ft_printf handle_char \
				handle_dec handle_hex handle_oct handle_perc handle_ptr \
				handle_unsigned handle_wchar handle_str handle_wstr

FILES		:=	$(addprefix ft_btree/, $(FT_BTREE)) \
				$(addprefix ft_char/, $(FT_CHAR)) \
				$(addprefix ft_conv/, $(FT_CONV)) \
				$(addprefix ft_lst/, $(FT_LST)) \
				$(addprefix ft_mem/, $(FT_MEM)) \
				$(addprefix ft_put/, $(FT_PUT)) \
				$(addprefix ft_str/, $(FT_STR)) \
				$(addprefix gnl/, $(GNL)) \
				$(addprefix ft_printf/, $(FT_PRINTF))

CFILES := $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OFILES := $(CFILES:.c=.o)

.PHONY: all clean fclean re

# rules
all: $(NAME)

$(OFILES): %.o: %.c
	@$(CC) -c $(CFLAGS) -I $(INC_DIR) $< -o $@

$(NAME): $(OFILES)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)
	@echo "\033[32mlibft.a created.\033[0m"

clean:
	@rm -f $(OFILES)
	@echo "\033[32mlibft object files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[32mlibft.a removed.\033[0m"

re: fclean all
