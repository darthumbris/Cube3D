/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 13:01:41 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/13 17:02:23 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "vectors.h"

# define M_PI_8		0.392699081698724154807830422909937860
# define M_PI32		4.712388980384689857693965074919254326
# define M_PI15_8	5.890486225480862322117456343649067907

typedef enum e_textures
{
	WEST = 0,
	EAST,
	NORTH,
	SOUTH,
	FLOOR,
	CEILING,
	WALL_1,
	WALL_2,
	WALL_3,
	WALL_4,
	WALL_5,
	WALL_6,
	WALL_7,
	WALL_8,
	WALL_9,
	WALL_10,
	FINISH_WALL,
	HIDDEN_WALL_1,
	HIDDEN_WALL_2,
	HIDDEN_WALL_3,
	HIDDEN_WALL_4,
	DOOR_WALL_1,
	DOOR_WALL_2,
	SPRITE_0,
	SPRITE_1,
	SPRITE_2,
	SPRITE_3,
	SPRITE_4,
	SPRITE_5,
	SPRITE_6,
	SPRITE_7,
	SPRITE_8,
	SPRITE_9,
	SPRITE_10,
	SPRITE_11,
	SPRITE_12,
	SPRITE_13,
	SPRITE_14,
	SPRITE_15,
	SPRITE_16,
	SPRITE_17,
	SPRITE_18,
	SPRITE_19,
	SPRITE_20,
	ITEM_0,
	ITEM_1,
	ITEM_2,
	ITEM_3,
	ITEM_4,
	ITEM_5,
	ITEM_6,
	ITEM_7,
	ITEM_8,
	DOOR_FRAME,
	HUD_MAIN,
	HUD_NUMBERS,
	HUD_FACES,
	SPRITESHEET_GUARD,
	SPRITESHEET_DOG
}	t_textures;

typedef enum e_sprites
{
	BARREL = SPRITE_0,
	PILLAR = SPRITE_1,
	LAMP = SPRITE_2,
	BONES = SPRITE_3,
	GUARD = SPRITE_4,
	DOG = SPRITE_5,
	TABLE = SPRITE_6,
	WELL_EMPTY = SPRITE_7,
	WELL_FULL = SPRITE_8,
	CHANDELIER = SPRITE_9,
	PLANT = SPRITE_10,
	TABLE_CHAIRS = SPRITE_11,
	STATUE = SPRITE_12,
	LAMP_STANDING = SPRITE_13,
	TREE = SPRITE_14,
	GREEN_BARREL = SPRITE_15,
	POT = SPRITE_16,
	FLAG = SPRITE_17,
	BONES_2 = SPRITE_18,
	DEAD_GUARD = SPRITE_19,
	PUDDLE = SPRITE_20,
}	t_sprite_enum;

typedef enum e_items
{
	STIMULANT = ITEM_0,
	MEDKIT = ITEM_1,
	SOUL = ITEM_2,
	DOGMEAL = ITEM_3,
	GUN = ITEM_4,
	AMMO = ITEM_5,
	TREASURE_0 = ITEM_6,
	TREASURE_1 = ITEM_7,
	TREASURE_2 = ITEM_8
}	t_items;

enum e_compas
{
	C_SOUTH,
	C_SOUTH_EAST,
	C_EAST,
	C_NORTH_EAST,
	C_NORTH,
	C_NORTH_WEST,
	C_WEST,
	C_SOUTH_WEST
};

typedef union u_lodtex
{
	mlx_texture_t	*texarr[SPRITESHEET_DOG + 2];
}	t_lodtex;

typedef union u_tex_path
{
	char	*path[SPRITESHEET_DOG + 2];
}			t_tex_path;

enum	e_state
{
	ALIVE,
	ATTACKING,
	DYING,
	DEAD
};

typedef struct s_sprite
{
	t_vector_double	map_pos;
	t_vector_double	dir;
	t_sprite_enum	kind;
	enum e_state	state;
	t_vector_int	transp_begin;
	t_vector_int	transp_end;
	double			dist;
	int				health;
	int				frame;
	int				last_attack;
	bool			dropped;
	bool			player_detected;
	bool			scanned_for_player;
	//bool			hidden;
}				t_sprite;

typedef struct s_sprite_lst
{
	t_sprite			sprite_data;
	struct s_sprite_lst	*next;
	struct s_sprite_lst	*prev;
}			t_sprite_lst;

typedef struct s_sprite_raycaster
{
	double			*zbuffer;
	t_vector_double	pos;
	double			inverse_determinant;
	t_vector_double	transform;
	int				sprite_screen_x;
	int				sprite_height;
	double			inverse_sprite_height;
	int				sprite_width;
	int				sprite_width_halve;
	double			inverse_sprite_width;
	t_vector_int	draw_start;
	t_vector_int	draw_end;
	t_vector_int	tex;
	double			inverse_transform_y;
}				t_sprite_raycaster;

t_sprite_lst	*new_sprite(t_sprite data);
t_sprite_lst	*add_sprite(t_sprite_lst **begin, t_sprite data);
void			clear_sprite_lst(t_sprite_lst **begin);
double			sprite_dist(t_vector_double start, t_vector_double end);
t_sprite_lst	*add_ammo_to_lst(t_sprite_lst **begin, t_sprite data);

#endif
