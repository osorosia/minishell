# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 19:29:20 by rnishimo          #+#    #+#              #
#    Updated: 2022/01/29 18:02:01 by rnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rcs

SRCS = ft_abs.c \
ft_abs_l.c \
ft_abs_ll.c \
ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isnumber.c \
ft_isprint.c \
ft_itoa.c \
ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstsize.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_numlen.c \
ft_numlen_base.c \
ft_numlen_u.c \
ft_numlen_u_base.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putnstr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_strdup_to_c.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strlen_to_c.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strndup.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
get_next_line.c \

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) libft.h
	$(AR) $(NAME) $(OBJS)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: bonus
bonus: all

.PHONY: norm
norm:
	norminette | grep Error

.PHONY: test
test: all
	cd ./.test && bash ./test.sh

.PHONY: tester
tester: all
	if [ ! -d ./libftTester ]; then git clone -q https://github.com/Tripouille/libftTester.git; fi
	cd libftTester && make m b

.PHONY: ls
ls:
	echo -n 'SRCS = ' && ls *.c | awk '{printf "%s \\\n", $$0}'
