/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 13:01:41 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/28 10:22:54 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "vectors.h"

typedef union u_lodsprites
{
	mlx_texture_t	*texarr[8];
}	t_lodsprites;

typedef enum e_sprites
{
	BARREL = 10,
	PILLAR = 11,
	LAMP = 12,
	DOOR_SPRITE = 13,
	BONES = 14,
	GUARD = 15,
	HIDDEN = 16,
	DOG = 17
}	t_sprite_enum;

typedef struct s_sprite
{
	t_vector_double	map_pos;
	t_sprite_enum	kind;
	bool			open;
	t_vector_int	transp_begin;
	t_vector_int	transp_end;
	double			dist;
	bool			hidden;
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
