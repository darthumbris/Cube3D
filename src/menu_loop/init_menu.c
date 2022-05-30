/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_menu.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:23:32 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/30 17:01:29 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	init_menu(t_data *data)
{
	t_vector_int	pos;

	init_hud(data);
	data->mlx.menu_screen = mlx_load_png("assets/hud/menu_screen.png");
	data->mlx.level_select = mlx_load_png("assets/hud/level_select.png");
	data->mlx.cursor = mlx_load_png("assets/hud/selector.png");
	data->mlx.map_editor_screen = mlx_load_png
		("assets/hud/map_editor_screen.png");
	if (data->mlx.menu_screen == NULL || data->mlx.level_select == NULL || \
		data->mlx.cursor == NULL)
		return (false);
	data->menu.cursor = true;
	data->menu.cursor_pos = 0;
	data->menu.menu_level = 0;
	data->menu.obj_button.pos0.x = 136 * data->hud.scale;
	data->menu.obj_button.pos1.x = 147 * data->hud.scale;
	data->menu.obj_button.pos0.x = 227 * data->hud.scale;
	data->menu.obj_button.pos1.x = 238 * data->hud.scale;
	data->menu.enemy_button.pos0.x = 301 * data->hud.scale;
	data->menu.enemy_button.pos1.x = 312 * data->hud.scale;
	data->menu.obj_button.pos0.y = 1 * data->hud.scale;
	data->menu.enemy_button.pos0.y = 1 * data->hud.scale;
	data->menu.floor_button.pos0.y = 1 * data->hud.scale;
	data->menu.obj_button.pos1.y = 12 * data->hud.scale;
	data->menu.enemy_button.pos1.y = 12 * data->hud.scale;
	data->menu.floor_button.pos1.y = 12 * data->hud.scale;
	pos.x = MENU_CURSOR_0_X_POS * data->hud.scale;
	pos.y = MENU_CURSOR_0_Y_START * data->hud.scale;
	draw_menu_screen(data, data->mlx.menu_screen);
	draw_cursor(data, pos);
	data->menu.update = false;
	return (true);
}
