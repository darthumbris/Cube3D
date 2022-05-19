/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   level_data.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 13:52:37 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 12:38:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVEL_DATA_H
# define LEVEL_DATA_H

# include "sprites.h"
# include "../libs/miniaudio.h"

# define MOVE_SPEED			7
# define ROTATE_SPEED		3
# define MOUSE_SENSITIV 	0.040
# define PICKUP_DIST		0.7

# define GUN_RANGE			150
# define KNIFE_RANGE		5
# define WEAPON_FOV			0.025
# define MELEE_FOV			0.55
# define DOG_MOVE_SPEED		0.04
# define GUARD_MOVE_SPEED	0.02
# define ENEMY_ROT_SPEED	2
# define ENEMY_RANGE		250
# define ENEMY_WARN_DIST	6
# define ENEMY_HEARING_DIST	75
# define PATROL_DIST		7

typedef struct s_player
{
	int				health;
	int				score;
	int				ammo;
	int				active_weapon;
	int				lives;
	bool			machine_gun_pickup;
	bool			game_over;
	int				secrets_found;
	int				treasure_found;
	int				enemies_killed;
	uint64_t		start_time;
	uint64_t		end_time;
	t_vector_double	start_pos;
	t_vector_double	start_dir;
	t_vector_double	start_plane;
}			t_player;

/**
 * @brief Struct for all the level data
 * 
 * @param map stores the map. (without the texture path and colour data) [x][y]
 * @param map_w total width of the map
 * @param map_h total height of the map
 * @param texture_path string of the path where texture is stored.
 * @param color color for the floor or ceiling stored in RGBA format.
 * 
 */
typedef struct s_level
{
	int			**wall_map;
	int			door_count;
	int			secret_count;
	int			map_w;
	int			map_h;
	char		**unparsed;
	char		**map;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	uint32_t	number_of_sprites;
	uint32_t	level_number;
	int			treasure_count;
	int			enemies_count;
	t_tex_path	paths;
}	t_level;

typedef struct s_config_data
{
	int				kind;
	char			*key;
	char			value;
	t_vector_int	transp_begin;
	t_vector_int	transp_end;
}			t_config_data;

typedef struct s_config
{
	t_config_data	*dat;
	int				size;
}			t_config;

typedef struct s_sound
{
	int				length;
	int				cur;
	ma_result		result;
	ma_engine		engine;
	ma_sound		**soundtrack;
	ma_sound_group	music_g;
	ma_sound_group	sfx_g;
}	t_sound;

#endif