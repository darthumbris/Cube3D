/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   level_data.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 13:52:37 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 14:06:41 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVEL_DATA_H
# define LEVEL_DATA_H

# include "sprites.h"
# include "../libs/miniaudio.h"

# define MOVE_SPEED		7
# define ROTATE_SPEED	3
# define MOUSE_SENSITIV 0.040
# define PICKUP_DIST	0.7

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
	bool			machine_gun_pickup;
	int				health;
	int				score;
	int				ammo;
	int				active_weapon;
	int				lives;
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
	char			**unparsed;
	char			**map;
	int				**wall_map;
	int				door_count;
	int				secret_count;
	int				map_w;
	int				map_h;
	t_tex_path		paths;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	unsigned int	number_of_sprites;
	unsigned int	level_number;
}	t_level;

typedef struct s_config_data
{
	char			*key;
	char			value;
	int				kind;
	t_vector_int	transp_begin;
	t_vector_int	transp_end;
}			t_config_data;

typedef struct s_config
{
	int				size;
	t_config_data	*dat;
}			t_config;

typedef struct s_sound
{
	ma_result		result;
	ma_engine		engine;
	ma_sound_group	music_g;
	ma_sound_group	sfx_g;
	ma_sound		**soundtrack;
	int				length;
	int				cur;
}	t_sound;

#endif