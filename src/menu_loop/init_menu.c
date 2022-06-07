/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_menu.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:23:32 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/07 09:51:05 by shoogenb      ########   odam.nl         */
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
	if (data->mlx.menu_screen == NULL || data->mlx.level_select == NULL || \
		data->mlx.cursor == NULL || data->mlx.check_mark == NULL)
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
	pos.x = MENU_CURSOR_0_X_POS * data->hud.scale;
	pos.y = MENU_CURSOR_0_Y_START * data->hud.scale;
	draw_menu_screen(data, data->mlx.menu_screen);
	draw_cursor(data, pos);
	data->menu.update = false;
	return (true);
}
