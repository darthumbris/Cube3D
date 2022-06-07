/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_menu.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:23:32 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/07 17:40:43 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	init_buttons(t_data *data)
{
	data->menu.obj_btn.rect.pos0.x = (int)(136 * data->hud.scale);
	data->menu.obj_btn.rect.pos1.x = (int)(147 * data->hud.scale);
	data->menu.enemy_btn.rect.pos0.x = (int)(227 * data->hud.scale);
	data->menu.enemy_btn.rect.pos1.x = (int)(238 * data->hud.scale);
	data->menu.floor_btn.rect.pos0.x = (int)(301 * data->hud.scale);
	data->menu.floor_btn.rect.pos1.x = (int)(312 * data->hud.scale);
	data->menu.obj_btn.rect.pos0.y = (int)(1 * data->hud.scale);
	data->menu.enemy_btn.rect.pos0.y = (int)(1 * data->hud.scale);
	data->menu.floor_btn.rect.pos0.y = (int)(1 * data->hud.scale);
	data->menu.obj_btn.rect.pos1.y = (int)(12 * data->hud.scale);
	data->menu.enemy_btn.rect.pos1.y = (int)(12 * data->hud.scale);
	data->menu.floor_btn.rect.pos1.y = (int)(12 * data->hud.scale);
	data->menu.enemy_btn.state = IDLE;
	data->menu.floor_btn.state = IDLE;
	data->menu.obj_btn.state = IDLE;
	data->menu.obj_btn.active = false;
	data->menu.enemy_btn.active = false;
	data->menu.floor_btn.active = false;
}

t_button	new_button(t_rect rect, char *txt)
{
	t_button	btn;

	btn.rect = rect;
	btn.active = false;
	btn.state = IDLE;
	btn.txt = txt;
	return (btn);
}

void	init_plane_ddlst(t_ddlst *p, double scale)
{
	int		i;
	t_rect	rect;

	p->elements = 3;
	p->height = 85 * scale;
	p->width = 7 * scale;
	p->pos.x = 5 * scale;
	p->pos.y = 27 * scale;
	p->btn_txt = ft_calloc(sizeof(char *), 3);
	p->btn_txt[0] = ft_strdup("plane 0");
	p->btn_txt[1] = ft_strdup("plane 1");
	p->btn_txt[2] = ft_strdup("plane 2");
	p->active.active = false;
	p->active.rect.pos0.x = 3 * scale;
	p->active.rect.pos0.y = 25 * scale;
	p->active.rect.pos1.x = 89 * scale;
	p->active.rect.pos1.y = 33 * scale;
	p->hvr_rct.pos0.x = 3 * scale;
	p->hvr_rct.pos0.y = 25 * scale;
	p->hvr_rct.pos1.x = 89 * scale;
	p->hvr_rct.pos1.y = 33 * scale;
	p->active.txt = p->btn_txt[0];
	p->btn_lst = ft_calloc(sizeof(t_button), 3);
	p->open_rct.pos0.x = p->active.rect.pos0.x;
	p->open_rct.pos1.x = p->active.rect.pos1.x;
	p->open_rct.pos0.y = p->active.rect.pos1.y;
	p->open_rct.pos1.y = p->active.rect.pos1.y + p->elements * 9 * scale + 1;
	p->outline.pos0.x = p->active.rect.pos0.x;
	p->outline.pos1.x = p->active.rect.pos1.x;
	p->outline.pos0.y = p->active.rect.pos1.y;
	p->outline.pos1.y = p->active.rect.pos1.y + 9 * scale;
	i = 0;
	rect.pos0.x = 3 * scale;
	rect.pos1.x = 89 * scale;
	while (i < 3)
	{
		rect.pos0.y = (34 + (i * 9)) * scale;
		rect.pos1.y = (42 + (i * 9)) * scale;
		p->btn_lst[i] = new_button(rect, p->btn_txt[i]);
		i++;
	}
}

void	init_floor_txt_strs(t_ddlst *f)
{
	f->btn_txt = ft_calloc(sizeof(char *), 10);
	f->btn_txt[0] = ft_strdup("greystone");
	f->btn_txt[1] = ft_strdup("bluestone");
	f->btn_txt[2] = ft_strdup("eagle");
	f->btn_txt[3] = ft_strdup("wood");
	f->btn_txt[4] = ft_strdup("door normal");
	f->btn_txt[5] = ft_strdup("door end");
	f->btn_txt[6] = ft_strdup("greystone e");
	f->btn_txt[7] = ft_strdup("greystone c");
	f->btn_txt[8] = ft_strdup("greystone h");
	f->btn_txt[9] = ft_strdup("wood eagle");
}

void	init_floor_ddlst(t_ddlst *f, double scale)
{
	int		i;
	t_rect	rect;

	f->elements = 10;
	f->height = 85 * scale;
	f->width = 7 * scale;
	f->pos.x = 5 * scale;
	f->pos.y = 50 * scale;
	init_floor_txt_strs(f);
	f->active.active = false;
	f->active.rect.pos0.x = 3 * scale;
	f->active.rect.pos0.y = 48 * scale;
	f->active.rect.pos1.x = 89 * scale;
	f->active.rect.pos1.y = 56 * scale;
	f->hvr_rct.pos0.x = 3 * scale;
	f->hvr_rct.pos0.y = 48 * scale;
	f->hvr_rct.pos1.x = 89 * scale;
	f->hvr_rct.pos1.y = 56 * scale;
	f->active.txt = f->btn_txt[0];
	f->btn_lst = ft_calloc(sizeof(t_button), 10);
	f->open_rct.pos0.x = 3 * scale;
	f->open_rct.pos1.x = 89 * scale;
	f->open_rct.pos0.y = 56 * scale;
	f->open_rct.pos1.y = 56 * scale + (f->elements * 9 * scale) + 1;
	f->outline.pos0.x = f->active.rect.pos0.x;
	f->outline.pos1.x = f->active.rect.pos1.x;
	f->outline.pos0.y = f->active.rect.pos1.y;
	f->outline.pos1.y = f->active.rect.pos1.y + 9 * scale;
	i = 0;
	rect.pos0.x = 3 * scale;
	rect.pos1.x = 89 * scale;
	while (i < 10)
	{
		rect.pos0.y = (57 + (i * 9)) * scale;
		rect.pos1.y = (65 + (i * 9)) * scale;
		f->btn_lst[i] = new_button(rect, f->btn_txt[i]);
		i++;
	}
}

void	init_dropdown_lists(t_menu *menu, double scale)
{
	init_plane_ddlst(&menu->plane_ddlst, scale);
	init_floor_ddlst(&menu->floor_ddlst, scale);
}

static bool	init_menu_textures(t_data *data)
{
	int	i;
	int	j;
	int	k;

	data->mlx.menu_screen = mlx_load_png("assets/hud/menu_screen.png");
	data->mlx.level_select = mlx_load_png("assets/hud/level_select.png");
	data->mlx.cursor = mlx_load_png("assets/hud/selector.png");
	data->mlx.map_editor_screen = mlx_load_png
		("assets/hud/map_editor_screen.png");
	data->mlx.check_mark = mlx_load_png("assets/hud/temp_active.png");
	data->mlx.font = mlx_load_png("assets/hud/font.png");
	data->mlx.menu_editor = mlx_new_image(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->mlx.menu_screen == NULL || data->mlx.level_select == NULL || \
		data->mlx.cursor == NULL || data->mlx.check_mark == NULL || \
		data->mlx.font == NULL)
		return (false);
	i = -1;
	while (++i < MAX_MAP_SIZE)
	{
		j = -1;
		while (++j < MAX_MAP_SIZE)
		{
			k = -1;
			while (++k < 3)
				data->menu.map[i][j][k] = 0;
		}
	}
	return (true);
}

bool	init_menu(t_data *data)
{
	t_vector_int	pos;

	init_hud(data);
	if (init_menu_textures(data) == false)
		return (false);
	data->menu.active_sprite = 1;
	data->menu.active_plane = 0;
	data->menu.map_zoom = 2;
	data->menu.map_offset.x = 149;
	data->menu.map_offset.y = 149;
	data->menu.map[0][0][0] = 1;
	data->menu.cursor = true;
	data->menu.cursor_pos = 0;
	data->menu.menu_level = 0;
	data->menu.map_area.pos0.x = 103 * data->hud.scale;
	data->menu.map_area.pos1.x = 315 * data->hud.scale;
	data->menu.map_area.pos0.y = 15 * data->hud.scale;
	data->menu.map_area.pos1.y = 232 * data->hud.scale;
	data->menu.grid_size = GRID_SIZE * data->hud.scale * data->menu.map_zoom;
	data->menu.max_tiles_on_map.x = 213 * data->hud.scale / data->menu.grid_size;
	data->menu.max_tiles_on_map.y = 218 * data->hud.scale / data->menu.grid_size;
	init_buttons(data);
	init_dropdown_lists(&data->menu, data->hud.scale);
	pos.x = MENU_CURSOR_0_X_POS * data->hud.scale;
	pos.y = MENU_CURSOR_0_Y_START * data->hud.scale;
	draw_menu_screen(data, data->mlx.menu_screen);
	draw_cursor(data, pos);
	data->menu.update = false;
	return (true);
}
