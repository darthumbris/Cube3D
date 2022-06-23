/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:38:14 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 15:33:20 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "vectors.h"
# include "icon.h"

# define SPRITE_LSTS	5
# define SPECIAL_LSTS	2
# define DIS_BTNS		3
# define PNT_BTNS		4

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

enum	e_sprite_lsts
{
	WALL,
	ZONE,
	DECOR,
	ITEM,
	ENEMY
};

enum	e_special_lsts
{
	ROTATION,
	DIFFICULTY
};

enum	e_dis_btns
{
	FLOOR,
	OBJ,
	ENMY
};

typedef struct s_sprite_drop_lists
{
	t_ddlst			drop[SPRITE_LSTS];
}	t_sprt_drop;

typedef struct s_special_drop_lists
{
	t_ddlst			drop[SPECIAL_LSTS];
}	t_sp_drop;

typedef struct s_display_btns
{
	t_button		btns[DIS_BTNS];
}	t_vis_btns;

typedef struct s_paint_btns
{
	t_button		btns[PNT_BTNS];
}	t_pnt_btns;

typedef struct s_file
{
	char			filenname[30];
	bool			reset_filename;
	t_button		load_btn;
	t_button		save_btn;
}	t_file;

typedef struct s_map_editor
{
	int				grid_size;
	int				map_zoom;
	int				active_plane;
	int				active_sprite;
	t_rect			map_area;
	uint8_t			map[200][200][3];
	t_vector_int	max_tiles_on_map;
	enum e_pen_mode	pen;
	t_vector_double	map_offset;
	t_ddlst			plane_ddlst;
	t_sprt_drop		sprt_drops;
	t_sp_drop		sp_drops;
	t_vis_btns		vis_btns;
	t_pnt_btns		pnt_btns;
	t_file			file;
}	t_map_edit;

typedef struct s_menu
{
	int				cursor_pos;
	int				menu_level;
	bool			update;
	bool			cursor;
	t_map_edit		editor;	
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