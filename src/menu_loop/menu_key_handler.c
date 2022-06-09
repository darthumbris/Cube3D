/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_key_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:39:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 14:25:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	escape_key(t_data *data)
{
	if (data->menu.menu_level == 0)
		close_game(data);
	else
	{
		mlx_set_cursor_mode(data->mlx.mlx_handle, MLX_MOUSE_DISABLED);
		data->menu.menu_level = 0;
		data->menu.cursor_pos = 0;
		data->menu.update = true;
		data->menu.cursor = true;
	}
}

static void	move_keys(t_data *data, struct mlx_key_data keys)
{
	if ((keys.key == MLX_KEY_UP || keys.key == MLX_KEY_W))
	{
		data->menu.cursor_pos--;
		if (data->menu.cursor_pos < 0)
			data->menu.cursor_pos = 0;
		data->menu.update = true;
	}
	if ((keys.key == MLX_KEY_DOWN || keys.key == MLX_KEY_S))
	{
		data->menu.cursor_pos++;
		if (data->menu.cursor_pos > 4 && data->menu.menu_level == 0)
			data->menu.cursor_pos = 4;
		else if (data->menu.cursor_pos > 5)
			data->menu.cursor_pos = 5;
		data->menu.update = true;
	}
}

static void	zoom_map(t_data *data, enum keys key, t_menu *menu)
{
	if (key == MLX_KEY_KP_SUBTRACT && menu->menu_level == 2)
	{
		menu->map_zoom--;
		if (menu->map_zoom < 1)
			menu->map_zoom = 1;
		menu->grid_size = GRID_SIZE * data->hud.scale * menu->map_zoom + 1;
		menu->update = true;
	}
	if (key == MLX_KEY_KP_ADD && menu->menu_level == 2)
	{
		menu->map_zoom++;
		if (menu->map_zoom > 8)
			menu->map_zoom = 8;
		menu->grid_size = GRID_SIZE * data->hud.scale * menu->map_zoom + 1;
		menu->update = true;
	}
}

static void	enter_key(t_data *data)
{
	if (data->menu.cursor_pos == 0)
	{
		data->menu.menu_level = 1;
		data->menu.update = true;
		data->menu.cursor_pos = 0;
	}
	else if (data->menu.cursor_pos == 3)
	{
		data->menu.menu_level = 2;
		data->menu.update = true;
		data->menu.cursor_pos = 0;
	}
	else if (data->menu.cursor_pos == 4)
		close_game(data);
}

void	menu_key_handler(struct mlx_key_data keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keys.action == MLX_RELEASE)
		return ;
	if (keys.key == MLX_KEY_ESCAPE)
		escape_key(data);
	if (is_movement_key(keys.key))
		move_keys(data, keys);
	if (keys.key == MLX_KEY_ENTER && data->menu.menu_level == 0)
		enter_key(data);
	if (keys.key == MLX_KEY_KP_ADD || keys.key == MLX_KEY_KP_SUBTRACT)
		zoom_map(data, keys.key, &data->menu);
}
