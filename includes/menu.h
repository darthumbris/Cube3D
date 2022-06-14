/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:38:14 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/14 15:01:53 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "vectors.h"
# include "icon.h"

enum	e_btn_state
{
	IDLE,
	HOVER,
	CLICKED
};

typedef struct s_rect
{
	t_vector_int	pos0;
	t_vector_int	pos1;
}	t_rect;

typedef struct s_button
{
	t_rect				rect;
	enum e_btn_state	state;
	bool				active;
	char				*txt;
	t_vector_int		icon_pos;
}				t_button;

typedef struct dropdownlist
{
	t_vector_int		pos;
	int					width;
	int					height;
	double				font_scale;
	unsigned int		elements;
	t_button			active;
	t_button			*btn_lst;
	char				**btn_txt;
	t_rect				open_rct;
	t_rect				outline;
	t_rect				hvr_rct;
	int					scroll_pos;
	int					max_visible;
}	t_ddlst;

enum	e_pen_mode
{
	BUCKET,
	PEN,
	AREA,
	PICKER
};

typedef struct s_menu
{
	int				cursor_pos;
	int				menu_level;
	int				grid_size;
	int				map_zoom;
	int				active_plane;
	int				active_sprite;
	char			filenname[30];
	bool			update;
	bool			cursor;
	bool			player_placed;
	bool			reset_filename;
	t_rect			map_area;
	uint8_t			map[200][200][3];
	t_ddlst			plane_ddlst;
	t_ddlst			rotate_ddlst;
	t_ddlst			wall_ddlst;
	t_ddlst			decor_ddlst;
	t_ddlst			enemy_ddlst;
	t_ddlst			item_ddlst;
	t_ddlst			zone_ddlst;
	t_button		obj_btn;
	t_button		enemy_btn;
	t_button		floor_btn;
	t_button		bucket_btn;
	t_button		picker_btn;
	t_button		area_btn;
	t_button		pen_btn;
	t_button		load_btn;
	t_button		save_btn;
	t_vector_int	player_pos;
	t_vector_int	max_tiles_on_map;
	enum e_pen_mode	pen;
	t_vector_double	map_offset;
}				t_menu;

# define MENU_CURSOR_0_X_POS	69
# define MENU_CURSOR_0_Y_START	86
# define MENU_CURSOR_0_JUMP		30
# define MENU_CURSOR_1_Y_START	48
# define MENU_CURSOR_1_JUMP		32
# define MENU_CURSOR_1_X_POS	4
# define GRID_SIZE				5.33333333333
# define MAX_MAP_SIZE			200
# define MAP_BORDER_COLOUR		0x848484FF
# define MAP_TRANSLATE_SPEED	0.3
# define HOVER_COLOR			0x7d7d7d7d
# define CLICKED_COLOR			0x424200ff

unsigned int	get_color_tile(int tile);
bool			is_hover(t_button *btn, int x, int y);
bool			is_mouse_in_rect(int x, int y, t_rect r);
int				get_button_mouse_on(int x, int y, t_ddlst drop);
void			scroll_function_btn(double x, double y, void *param);
bool			is_wall_lst(int tile);
bool			is_zone_lst(int tile);
bool			is_decor_lst(int tile);
bool			is_item_lst(int tile);
bool			is_movable_lst(int tile);
// int				get_correct_plane(int active_plane);

#endif