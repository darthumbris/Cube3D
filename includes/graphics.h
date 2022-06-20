/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 13:46:23 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/20 14:19:19 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

// # include "../libs/MLX42/include/MLX42/MLX42.h"
# include "sprites.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
//time.h only for the score screen to display how long player
//takes to finish the level.
# include <sys/time.h>

# define SCREEN_HEIGHT		720
# define SCREEN_WIDTH		960
# define FOV				70
# define RENDER_DIST_S		400

# define VIEW_LINE_COLOUR	0xD7FFFFFF
# define WALL_COLOUR 		0xD8D8FCFF
# define BORDER_COLOR		4282400768
# define MENU_BORDER_COLOR	0x880000FF

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

# define SCORE_NBR_SIZE		12
# define PERCENTAGE_POS_X	132
# define COLON_POS_X		120
# define NBR_STARTPOS_X		170
# define TIME_POS_Y			76
# define PAR_POS_Y			91
# define BONUS_POS_Y		113
# define KILL_POS_Y			135
# define SECRET_POS_Y		152
# define TREASURE_POS_Y		169

enum	e_hud_textures
{
	HUD_M_T,
	HUD_N_T,
	HUD_F_T,
	SCORE_M_T,
	SCORE_N_T,
	GAMEOVER_T
};

enum	e_weapon_textures
{
	PISTOL0_T,
	PISTOL1_T,
	PISTOL2_T,
	PISTOL3_T,
	KNIFE0_T,
	KNIFE1_T,
	KNIFE2_T,
	KNIFE3_T,
	MACHINEGUN0_T,
	MACHINEGUN1_T,
	MACHINEGUN2_T,
	MACHINEGUN3_T,
};

typedef struct s_lodtex
{
	mlx_texture_t	*wall[51];
	mlx_texture_t	*obj[69];
	mlx_texture_t	*enmy[23];
	mlx_texture_t	*hud[6];
	mlx_texture_t	*wpn[12];
}	t_lodtex;

typedef struct s_texture_in_map
{
	bool	wall[51];
	bool	obj[69];
	bool	enmy[23];
}	t_txtr_in_map;

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
	int				max_size_score_nbrs;
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
	mlx_image_t		*score_screen;
	mlx_image_t		*menu_editor;
	mlx_image_t		*menu_editor_fg;
	t_txtr_in_map	txt_in_map;
	mlx_texture_t	*numbers;
	mlx_texture_t	*faces;
	mlx_texture_t	*hud_texture;
	mlx_texture_t	*menu_screen;
	mlx_texture_t	*level_select;
	mlx_texture_t	*map_editor_screen;
	mlx_texture_t	*cursor;
	mlx_texture_t	*check_mark;
	mlx_texture_t	*font;
	mlx_texture_t	*wall_icons;
	mlx_texture_t	*obj_icons;
	mlx_texture_t	*enmy_icons;
	mlx_texture_t	*item_icons;
	mlx_texture_t	*zone_icons;
	mlx_texture_t	*dir_icons;
	t_weapon_anim	weapon_anim[3];
}			t_mlx;

void	draw_texture(mlx_image_t *img, mlx_texture_t *tex, \
					t_vector_int start, double scale);
void	draw_texture_area(mlx_image_t *img, mlx_texture_t *tex, \
					t_vector_int start, t_vector_int tex_pos, \
					int wh[2], double scale);

#endif
