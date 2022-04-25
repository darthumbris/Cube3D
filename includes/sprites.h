/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 13:01:41 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/25 16:31:05 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

//# include "cubed.h"
# include "vectors.h"

typedef union u_lodsprites
{
	mlx_texture_t	*texarr[6];
	struct {
		mlx_texture_t	*sprite0_texture;
		mlx_texture_t	*sprite1_texture;
		mlx_texture_t	*sprite2_texture;
		mlx_texture_t	*door_texture;
		mlx_texture_t	*sprite3_texture;
		mlx_texture_t	*sprite4_texture;
	};
}	t_lodsprites;

typedef enum e_sprites
{
	BARREL = 0,
	PILLAR = 1,
	LAMP = 2,
	DOOR_SPRITE = 3,
	BONES = 4,
	GUARD = 5
}	t_sprite_enum;

typedef struct s_sprite
{
	t_vector_double	map_pos;
	t_sprite_enum	kind;
	bool			open;
}				t_sprite;

typedef struct s_sprite_lst
{
	t_sprite			sprite_data;
	struct s_sprite_lst	*next;
}			t_sprite_lst;

typedef struct s_sprite_raycaster
{
	double			*zbuffer;
	int				*sprite_order;
	double			*sprite_distance;
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

// typedef struct s_door
// {
// 	bool			rotated;
// 	bool			inverted;
// 	t_vector_double	pos;
// 	t_vector_double	end_pos;
// 	double			dist;
// 	double			end_dist;
// 	double			angle;
// 	double			end_angle;
// 	double			view_distance;
// 	double			cur_angle;
// 	int				draw_x;
// 	int				draw_y;
// 	int				draw_width;
// 	int				draw_height;
// 	double			ratio;
// 	double			ratio2;
// 	int				offset_x;
// 	int				offset_y;
// }			t_door;

t_sprite_lst	*new_sprite(t_sprite data);
t_sprite_lst	*add_sprite(t_sprite_lst **begin, t_sprite data);
void			clear_sprite_lst(t_sprite_lst **begin);

#endif
