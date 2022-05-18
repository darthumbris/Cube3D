/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 13:46:23 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 14:23:46 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "sprites.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <time.h>

# define SCREEN_HEIGHT		768
# define SCREEN_WIDTH		1024
# define FOV				70
# define RENDER_DIST_S		400

# define VIEW_LINE_COLOUR	0xD7FFFFFF
# define WALL_COLOUR 		0xD8D8FCFF
# define BORDER_COLOR		4282400768

//FIXED VALUES DONT CHANGE
# define MINIMAP_WIDTH		61
# define MINIMAP_HEIGHT		31
# define SCORE_DIGIT_0_POS	55
# define SCORE_DIGIT_1_POS	63
# define SCORE_DIGIT_2_POS	71
# define SCORE_DIGIT_3_POS	79
# define SCORE_DIGIT_4_POS	87
# define LEVEL_DIGIT_POS	24
# define LIVES_DIGIT_POS	112
# define HEALTH_DIGIT_0_POS	168
# define HEALTH_DIGIT_1_POS	176
# define HEALTH_DIGIT_2_POS	184
# define AMMO_DIGIT_0_POS	216
# define AMMO_DIGIT_1_POS	224
# define FACES_POS			134
# define MINIMAP_POS		71

typedef union u_lodtex
{
	mlx_texture_t	*texarr[MACHINEGUN3 + 2];
}	t_lodtex;

typedef struct s_weapon_animation
{
	int				frame;
	int				range;
	bool			animate;
	mlx_texture_t	*tex0;
	mlx_texture_t	*tex1;
	mlx_texture_t	*tex2;
	mlx_texture_t	*tex3;
}			t_weapon_anim;

enum e_weapons
{
	PISTOL,
	KNIFE,
	MACHINEGUN
};

typedef struct s_hud
{
	int				max_height;
	int				max_width;
	int				max_size_faces;
	int				max_size_numbers;
	int				face_pos_x;
	int				border_width;
	double			inv_scale;
	double			scale;
	t_vector_int	pos_map;
	t_vector_int	pos_hud;
}	t_hud;

/**
 * @brief Struct for all the mlx data
 * 
 * @param mlx_handle mlx handle for the window and everything to do with mlx
 * @param bg background image (used for floor and ceiling)
 * @param fg foreground image (used for drawing the walls)
 * @param texture the mlx texture data.
 */
typedef struct s_mlx
{
	int				minimap_zoom;
	double			minimap_scale;
	double			hud_scale;
	mlx_t			*mlx_handle;
	t_lodtex		tex;
	mlx_image_t		*bg;
	mlx_image_t		*fg;
	mlx_image_t		*weapon;
	mlx_image_t		*hud;
	mlx_image_t		*minimap;
	mlx_texture_t	*numbers;
	mlx_texture_t	*faces;
	mlx_texture_t	*hud_texture;
	t_weapon_anim	weapon_anim[3];
}			t_mlx;

#endif