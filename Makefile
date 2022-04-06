# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: shoogenb <shoogenb@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/06 13:12:52 by shoogenb      #+#    #+#                  #
#    Updated: 2022/04/06 13:25:08 by shoogenb      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cube3D

CC 	:= gcc
COMPILE_FLAGS = -Wall -Wextra -Werror
LINKING_FLAGS = libmlx42.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC =	main.c \

SRC_EXT = c

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:%.$(SRC_EXT)=%.o))
SRC :=  $(addprefix $(SRC_DIR)/, $(SRC))

INC = -I $(INC_DIR)

COM_COLOR   = \033[0;33m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
PRG_COLOR	= \033[0;35m

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

all: libmlx42.a $(NAME)

$(NAME): $(OBJ)
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

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT) | $(OBJ_DIR)
	
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
	@make -C lib/MLX42
	@cp lib/MLX42/libmlx42.a .

clean:
	@printf "%b" "$(ERROR_COLOR)Removing $(OBJ_COLOR)object files\n"
	@rm -rf $(OBJ_DIR)
	@make -C lib/MLX42 clean
	@echo "Objects cleaned."

fclean: clean
	@printf "%b" "$(ERROR_COLOR)Removing $(PRG_COLOR)$(NAME)\n"
	@rm -f $(NAME)
	@make -C lib/MLX42 fclean
	@rm -f libmlx42.a
	@echo "Binaries cleaned."

re: fclean all

.PHONY: all clean fclean re
