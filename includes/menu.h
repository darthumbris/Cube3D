/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:38:14 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/07 17:38:34 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "vectors.h"

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
}				t_button;

typedef struct dropdownlist
{
	t_vector_int		pos;
	int					width;
	int					height;
	unsigned int		elements;
	t_button			active;
	t_button			*btn_lst;
	char				**btn_txt;
	t_rect				open_rct;
	t_rect				outline;
	t_rect				hvr_rct;
}	t_ddlst;

typedef struct s_menu
{
	int				cursor_pos;
	int				menu_level;
	bool			update;
	bool			cursor;
	t_button		obj_btn;
	t_button		enemy_btn;
	t_button		floor_btn;
	t_rect			map_area;
	uint8_t			map[200][200][3];
	int				grid_size;
	int				map_zoom;
	t_vector_double	map_offset;
	t_vector_int	max_tiles_on_map;
	t_ddlst			plane_ddlst;
	t_ddlst			floor_ddlst;
	t_ddlst			obj_ddlst;
	t_ddlst			enemy_ddlst;
	int				active_plane;
	int				active_sprite;
}				t_menu;

# define MENU_CURSOR_0_X_POS	69
# define MENU_CURSOR_0_Y_START	86
# define MENU_CURSOR_0_JUMP		30
# define MENU_CURSOR_1_Y_START	48
# define MENU_CURSOR_1_JUMP		32
# define MENU_CURSOR_1_X_POS	4
# define GRID_SIZE				3
# define MAX_MAP_SIZE			200
# define MAP_BORDER_COLOUR		0x848484FF
# define MAP_TRANSLATE_SPEED	0.3
# define HOVER_COLOR			0x7d7d7d7d
# define CLICKED_COLOR			0x424200ff

unsigned int	get_color_tile(int tile);
bool			is_hover(t_button *btn, int x, int y);
bool			is_mouse_in_rect(int x, int y, t_rect r);
int				get_button_mouse_on(int x, int y, t_ddlst drop);

#endif