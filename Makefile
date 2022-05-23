# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: shoogenb <shoogenb@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/06 13:12:52 by shoogenb      #+#    #+#                  #
#    Updated: 2022/05/23 12:08:39 by shoogenb      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cube3D

CC  := gcc
COMPILE_FLAGS = -Wall -Wextra -Werror
LINKING_FLAGS = libmlx42.a libft.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRC =	main.c \
        graphics/init_mlx_struct.c \
        graphics/raycaster.c \
		graphics/raycaster_utils.c \
        graphics/draw_background.c \
		graphics/draw_foreground.c \
        game_loop.c \
		parser/parse_input.c \
		parser/parsefcval.c \
		parser/parsetextures.c \
		parser/parsemap.c \
		parser/parsemap_utils.c \
		parser/parser_utils.c \
		parser/parse_validation.c
		

SRC_EXT = c

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:%.$(SRC_EXT)=%.o))
SRC :=  $(addprefix $(SRC_DIR)/, $(SRC))

INC = -I $(INC_DIR)

HEADERS = cubed.h
HEADERS :=  $(addprefix $(INC_DIR)/, $(HEADERS))

COM_COLOR   = \033[0;33m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
PRG_COLOR   = \033[0;35m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

ifeq ($(DEBUG),1)
	COMPILE_FLAGS += -g3
	COM_STRING = "Compiling[DEBUG]"
endif
ifeq ($(DEBUG),2)
	COMPILE_FLAGS += -g3 -fsanitize=address
	COM_STRING = "Compiling[LEAKS]"
endif

all: libmlx42.a libft.a $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@$(CC) $(COMPILE_FLAGS) $(OBJ) -o $(NAME) $(LINKING_FLAGS) 2> $@.log; \
		RESULT=$$?; \
		if [ $$RESULT -ne 0 ]; then \
			printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(PRG_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
		elif [ -s $@.log ]; then \
			printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(PRG_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
		else  \
			printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(PRG_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
		fi; \
		cat $@.log; \
		rm -f $@.log; \
		exit $$RESULT

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT) $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(COMPILE_FLAGS) $(INC) -c -o $@ $< 2> $@.log; \
		RESULT=$$?; \
		if [ $$RESULT -ne 0 ]; then \
			printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
		elif [ -s $@.log ]; then \
			printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
		else  \
			printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
		fi; \
		cat $@.log; \
		rm -f $@.log; \
		exit $$RESULT

libmlx42.a:
	@make -C libs/MLX42
	@cp libs/MLX42/libmlx42.a .

libft.a:
	@make -C libs/libft
	@cp libs/libft/libft.a .

clean:
	@printf "%b" "$(ERROR_COLOR)Removing $(OBJ_COLOR)object files\n"
	@rm -rf $(OBJ_DIR)
	@make -C libs/MLX42 clean
	@make -C libs/libft clean
	@echo "Objects cleaned."

fclean: clean
	@printf "%b" "$(ERROR_COLOR)Removing $(PRG_COLOR)$(NAME)\n"
	@rm -f $(NAME)
	@make -C libs/MLX42 fclean
	@make -C libs/libft fclean
	@rm -f libmlx42.a
	@rm -f libft.a
	@echo "Binaries cleaned."

re: fclean all

.PHONY: all clean fclean re

