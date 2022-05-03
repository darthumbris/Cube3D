/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 13:01:41 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/03 12:38:03 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "vectors.h"

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
	HUD_MAIN,
	HUD_NUMBERS,
	HUD_FACES
}	t_textures;

typedef enum e_sprites
{
	BARREL = SPRITE_0,
	PILLAR = SPRITE_1,
	LAMP = SPRITE_2,
	DOOR_SPRITE = SPRITE_3,
	BONES = SPRITE_4,
	GUARD = SPRITE_5,
	HIDDEN = SPRITE_6,
	DOG = SPRITE_7,
	TABLE = SPRITE_8,
	WELL_EMPTY = SPRITE_9,
	WELL_FULL = SPRITE_10,
	CHANDELIER = SPRITE_11,
	PLANT = SPRITE_12,
	TABLE_CHAIRS = SPRITE_13,
	HIDDEN_2 = SPRITE_14,
	STATUE = SPRITE_15,
	LAMP_STANDING = SPRITE_16,
	TREE = SPRITE_17,
	GREEN_BARREL = SPRITE_18,
	POT = SPRITE_19,
	FLAG = SPRITE_20
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

typedef union u_lodtex
{
	mlx_texture_t	*texarr[HUD_FACES + 1];
}	t_lodtex;

typedef union u_tex_path
{
	char	*path[HUD_FACES + 1];
}			t_tex_path;

typedef struct s_sprite
{
	t_vector_double	map_pos;
	t_sprite_enum	kind;
	bool			open;
	t_vector_int	transp_begin;
	t_vector_int	transp_end;
	double			dist;
	bool			hidden;
	uint32_t		timer;
}				t_sprite;

typedef struct s_sprite_lst
{
	t_sprite			sprite_data;
	struct s_sprite_lst	*next;
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

#endif
