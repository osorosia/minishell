# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 19:29:20 by rnishimo          #+#    #+#              #
#    Updated: 2022/07/02 20:52:55 by rnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR += ft_free/
SRCS += $(addprefix ft_free/, \
	ft_free_strs.c \
	)

OBJ_DIR += ft_is/
SRCS += $(addprefix ft_is/, \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isnumber.c \
	ft_isprint.c \
	ft_isspace.c \
	)

OBJ_DIR += ft_mem/
SRCS += $(addprefix ft_mem/, \
	ft_bzero.c \
	ft_calloc.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	)

OBJ_DIR += ft_num/
SRCS += $(addprefix ft_num/, \
	ft_numlen.c \
	ft_unumlen.c \
	)

OBJ_DIR += ft_printf/
SRCS += $(addprefix ft_printf/, \
	ft_printf.c \
	spec_c.c \
	spec_d.c \
	spec_p.c \
	spec_s.c \
	spec_u.c \
	spec_xX.c \
	spec.c \
	)

OBJ_DIR += ft_printf_x/
SRCS += $(addprefix ft_printf_x/, \
	ft_printf_x.c \
	xspec_d.c \
	xspec_s.c \
	xspec.c \
	)

OBJ_DIR += ft_put/
SRCS += $(addprefix ft_put/, \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_base_fd.c \
	ft_putnbr_fd.c \
	ft_putnstr_fd.c \
	ft_putstr_fd.c \
	ft_putunbr_base_fd.c \
	)

OBJ_DIR += ft_str/
SRCS += $(addprefix ft_str/, \
	ft_atoi.c \
	ft_itoa.c \
	ft_split.c \
	ft_strchr.c \
	ft_strcmp.c \
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
	)

OBJ_DIR += ft_x/
SRCS += $(addprefix ft_x/, \
	ft_xcalloc.c \
	ft_xitoa.c \
	ft_xitoa_base.c \
	ft_xsplit.c \
	ft_xstrdup.c \
	ft_xstrdup_to_c.c \
	ft_xstrjoin.c \
	ft_xstrjoin_with_free.c \
	ft_xstrndup.c \
	)

OBJ_DIR += ft_xstd/
SRCS += $(addprefix ft_xstd/, \
	ft_xclose.c \
	ft_xmalloc.c \
	ft_xopen.c \
	ft_xread.c \
	)

OBJ_DIR += get_next_line/
SRCS += $(addprefix get_next_line/, \
	get_next_line.c \
	xget_next_line.c \
	)

OBJS = $(SRCS:%.c=obj/%.o)
OBJ_DIR := $(addprefix obj/, $(OBJ_DIR))
OBJ_DIR := $(addsuffix .keep, $(OBJ_DIR))

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

obj/%.o: %.c libft.h $(OBJ_DIR)
	gcc $(CFLAGS) -I. -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(@D)
	touch $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette | grep -v 'OK!' || echo norm: OK

.PHONY: all clean fclean re norm
