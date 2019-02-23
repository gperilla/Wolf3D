# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperilla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 16:43:17 by gperilla          #+#    #+#              #
#    Updated: 2018/02/19 17:00:03 by gperilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3D

CC = gcc

WARNINGS = -Werror -Wextra -Wall \
		   $(shell sdl-config --cflags)

INC = -I. -I libft/ -I libft/ft_printf/ -I includes -I minilibx_macos

LIB = -L libft/ -lft \
	  -L minilibx_macos -lmlx -framework OpenGL -framework appKit \
	  -lpthread \
	  $(shell sdl-config --libs) -lSDL_mixer

OBJC = main.c \
	   my_putpixel.c \
	   helpers.c \
	   parser.c \
	   helpers2.c \
	   inits.c \
	   get_pixel_color.c \
	   portal_drawing.c \
	   portal_drawing2.c \
	   portal_drawing_position.c \
	   view_through_portal3.c \
	   view_through_portal2.c \
	   view_through_portal.c \
	   map_travelling.c \
	   wall_drawing.c \
	   wall_drawing2.c \
	   floor_drawing.c \
	   sky_drawing.c \
	   world_thread.c \
	   end_game.c \
	   quick_save.c \
	   key_press_events.c \
	   other_events.c \
	   move_through.c \
	   move_through_portal.c \
	   movements.c \
	   movements2.c \
	   shoot_portal.c \
	   creator.c \
	   game_loop.c \

OBJ = $(addprefix .obj/, $(OBJC:.c=.o))

SRCS = $(addprefix srcs/, $(OBJC))



define AUTHORS
gperilla
endef
export AUTHORS

COLOR = $(shell bash -c 'echo $$RANDOM')

define SIGN
	@/bin/echo -n "by: "
	@/bin/echo $$AUTHORS
endef

define OK
	@$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	@echo -n $1
	$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	@echo ' [Compiled]'
	@tput sgr0
endef

define ISOK
	@$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	@echo $1 '[Ready]'
	@tput sgr0
	@$(call SIGN , $(NAME))
endef



all: $(NAME) auteur
ifndef SILENT
	@$(call ISOK, $(NAME))
endif
	@:

$(NAME): $(OBJ)
	@make --silent -C minilibx_macos
	@make -C libft
	@$(CC) $(INC) $(WARNINGS) $(LIB) $(OBJ) -o $@

test:
	@make --silent -C minilibx_macos
	@make -j4 -C libft SILENT=1
	@$(CC) $(INC) $(LIB) $(SRCS) -o $(NAME)
	@tput smso
	@echo 'test it'

fast:
	@make --silent -C minilibx_macos
	@make -j4 -C libft SILENT=1
	@make SILENT=1
	@$(call ISOK, $(NAME))

.obj/%.o: srcs/%.c
	@gcc -c $(INC) $(WARNINGS) $< -o $@ $(OPTIONS)
ifndef SILENT
	$(call OK, $*)
endif

auteur:
	@touch auteur
	@/bin/echo "$$AUTHORS" > auteur

init: auteur
	@mkdir -p srcs
	@mkdir -p .obj

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@echo 'removed .o'

fclean: clean
	@make --silent -C minilibx_macos clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@echo 'All your base are belong to us'

re: fclean all

.PHONY: all clean fclean re test auteur
