# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: shoogenb <shoogenb@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/06 13:12:52 by shoogenb      #+#    #+#                  #
#    Updated: 2022/05/17 13:59:29 by pvan-dij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cube3D_bonus

CC  := gcc
COMPILE_FLAGS = -Wall -Wextra -Werror -o3 -Wno-enum-compare #last flag is for linux compilation
LINKING_FLAGS = $(MLX) $(LIBFT) -pthread -lm -ldl -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
#pthread also linux
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = ./libs/libft
MLX_DIR = ./libs/MLX42

SRC =	main.c \
        graphics/init_mlx_struct.c \
        graphics/raycaster.c \
		graphics/raycaster_utils.c \
        graphics/draw_background.c \
		graphics/draw_walls.c \
		graphics/draw_foreground.c \
		graphics/draw_transparency.c \
		graphics/draw_sprites.c \
		graphics/sprite_lst_functions.c \
		graphics/sprite_utils.c \
		graphics/draw_hud.c \
		graphics/draw_hud_utils.c \
		graphics/draw_minimap.c \
		graphics/door_utils.c \
		graphics/draw_minimap_utils.c \
		graphics/extend_ray.c \
		graphics/extend_ray_utils.c \
		graphics/draw_weapons.c \
		graphics/extend_ray_secret.c \
		graphics/draw_enemies.c \
		graphics/minimap_procedural.c \
		graphics/draw_enemies_utils.c \
        game_loop.c \
		sound.c \
		mouse_functions.c \
		key_functions.c \
		update_objects.c \
		update_items.c \
		camera_functions.c \
		cleunup_functions.c \
		check_weapon_hit.c \
		parser/parse_input.c \
		parser/parsefcval.c \
		parser/parsetextures.c \
		parser/parsemap.c \
		parser/parser_utils.c \
		parser/parse_validation.c \
		parser/is_what_tile.c \
		parser/is_enemy.c \
		parser/set_sprite_data.c \
		parser/special_tiles.c \
		parser/parse_config.c \
		parser/check_textures.c \
		parser/init_doormap.c \
		enemy_processes/path_find.c \
		enemy_processes/path_find_2.c \
		enemy_processes/path_find_3.c \
		enemy_processes/path_find_directions.c \
		enemy_processes/path_find_utils.c \
		enemy_processes/path_find_patrol.c \
		enemy_processes/enemy_ai_0.c \
		enemy_processes/enemy_ai_1.c \
		enemy_processes/check_enemy_collision.c \
		enemy_processes/enemy_attack.c \
		

SRC_EXT = c

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:%.$(SRC_EXT)=%.o))
SRC :=  $(addprefix $(SRC_DIR)/, $(SRC))

INC = -I $(INC_DIR)

HEADERS = cubed.h sprites.h vectors.h
HEADERS :=  $(addprefix $(INC_DIR)/, $(HEADERS))

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx42.a

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
	COMPILE_FLAGS += -g3 -D DEBUG_MODE=1
	COM_STRING = "Compiling[DEBUG]"
endif
ifeq ($(DEBUG),2)
	COMPILE_FLAGS += -g3 -fsanitize=address
	COM_STRING = "Compiling[LEAKS]"
endif

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ) $(HEADERS)
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

$(MLX):
	@make -C $(MLX_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@printf "%b" "$(ERROR_COLOR)Removing $(OBJ_COLOR)object files\n"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean
	@echo "Objects cleaned."

fclean: clean
	@printf "%b" "$(ERROR_COLOR)Removing $(PRG_COLOR)$(NAME)\n"
	@rm -f $(NAME)
	@rm -f cube3D
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) fclean
	@rm -f libmlx42.a
	@echo "Binaries cleaned."

re: clean all #TODO:re fclean rule

.PHONY: all clean fclean re

