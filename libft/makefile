# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperilla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 16:43:17 by gperilla          #+#    #+#              #
#    Updated: 2018/02/13 15:31:33 by gperilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifdef VERBOSE
.SILENT: all clean fclean %.o
endif

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

OBJC = 	ft_rot.c \
		ft_atoi.c \
		ft_itoa.c \
		my_math.c \
		ft_bzero.c \
		ft_printf.c \
		ft_memset.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_strcat.c \
		ft_strcpy.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_strmap.c \
		ft_putnbr.c \
		ft_strequ.c \
		ft_lstadd.c \
		ft_strstr.c \
		ft_strrev.c \
		ft_lstmap.c \
		ft_lstdel.c \
		ft_lstnew.c \
		ft_putstr.c \
		ft_strsub.c \
		ft_memcpy.c \
		ft_lstiter.c \
		ft_isblank.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_strncpy.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_islower.c \
		ft_isupper.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_striter.c \
		ft_strnequ.c \
		ft_strmapi.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_putchar.c \
		ft_putendl.c \
		ft_pbuffer.c \
		ft_strsplit.c \
		ft_memalloc.c \
		ft_striteri.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_lstdelone.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		get_next_line.c \
		ft_pprint_base.c \
		ft_psigned_dec.c \
		ft_pflags_usage.c \
		ft_pstart_print.c \
		ft_strjoin_free.c \
		ft_pflags_checks.c \
		ft_pflags_checks2.c \
		ft_punsigned_char.c \
		ft_punsigned_base.c \
		ft_pprintf_widechar.c \
		ft_punsigned_string.c \
		ft_punsigned_string2.c \

OBJ = $(OBJC:.c=.o)

COLOR = $(shell bash -c 'echo $$RANDOM')

define OK
	@$(eval COLOR=$(shell echo $$((($(COLOR)-15) % 232 + 16))))
	@tput setaf $(COLOR)
	@echo $1 '[Compiled]'
endef

define ISOK
	@grep -o . <<< $1 | while read -n1 c; do \
		echo "$$c"; done
endef

define ISOK2
	@$(eval COLOR=$(shell echo $$((($(COLOR)-1)))))
	clr=$(COLOR); \
	echo '$1 [Compiled]' | grep -o . | sed 's/ //g' | while read ch; do \
	clr=$$(($$clr+1)); \
	tput setaf $$clr; \
	printf "%s" $$ch; done
	echo ''
endef

all: $(NAME)
	@:

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
ifndef SILENT
	@tput smso;
	@$(call ISOK2, $@)
	@tput sgr0
endif

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@
ifndef SILENT
	@$(call ISOK2, $*)
endif

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
