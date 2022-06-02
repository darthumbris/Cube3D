/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 13:53:40 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/02 17:11:21 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//TODO make cleanup work properly in all states
void	close_game(t_data *data)
{
	// cleanup_data(data);
	mlx_close_hook(data->mlx.mlx_handle, menu_loop, data);
	mlx_close_window(data->mlx.mlx_handle);
	exit(EXIT_SUCCESS);
}

void	menu_key_handler(struct mlx_key_data keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keys.key == MLX_KEY_ESCAPE && keys.action != MLX_RELEASE)
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
	if ((keys.key == MLX_KEY_UP || keys.key == MLX_KEY_W) && \
		keys.action != MLX_RELEASE)
	{
		data->menu.cursor_pos--;
		if (data->menu.cursor_pos < 0)
			data->menu.cursor_pos = 0;
		data->menu.update = true;
	}
	if ((keys.key == MLX_KEY_DOWN || keys.key == MLX_KEY_S) && \
		keys.action != MLX_RELEASE)
	{
		data->menu.cursor_pos++;
		if (data->menu.cursor_pos > 4 && data->menu.menu_level == 0)
			data->menu.cursor_pos = 4;
		else if (data->menu.cursor_pos > 5)
			data->menu.cursor_pos = 5;
		data->menu.update = true;
	}
	if (keys.key == MLX_KEY_ENTER && data->menu.menu_level == 0 && \
		keys.action != MLX_RELEASE)
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
	if (keys.key == MLX_KEY_KP_SUBTRACT && data->menu.menu_level == 2 && \
		keys.action != MLX_RELEASE)
	{
		data->menu.map_zoom--;
		if (data->menu.map_zoom < 1)
			data->menu.map_zoom = 1;
		data->menu.grid_size = GRID_SIZE * data->hud.scale * data->menu.map_zoom;
		data->menu.update = true;
	}
	if (keys.key == MLX_KEY_KP_ADD && data->menu.menu_level == 2 && \
		keys.action != MLX_RELEASE)
	{
		data->menu.map_zoom++;
		if (data->menu.map_zoom > 8)
			data->menu.map_zoom = 8;
		data->menu.grid_size = GRID_SIZE * data->hud.scale * data->menu.map_zoom;
		data->menu.update = true;
	}
}

void	move_map(t_data *data)
{
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_LEFT) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_A))
	{
		data->menu.map_offset.x -= MAP_TRANSLATE_SPEED;
		if (data->menu.map_offset.x < -.4)
			data->menu.map_offset.x = -.4;
		data->menu.update = true;
	}
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_RIGHT) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_D))
	{
		data->menu.map_offset.x += MAP_TRANSLATE_SPEED;
		if (data->menu.map_offset.x > MAX_MAP_SIZE - data->menu.max_tiles_on_map.x + 0.1)
			data->menu.map_offset.x = MAX_MAP_SIZE - data->menu.max_tiles_on_map.x + 0.1;
		data->menu.update = true;
	}
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_DOWN) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_S))
	{
		data->menu.map_offset.y += MAP_TRANSLATE_SPEED;
		if (data->menu.map_offset.y > MAX_MAP_SIZE - data->menu.max_tiles_on_map.y + 0.1)
			data->menu.map_offset.y = MAX_MAP_SIZE - data->menu.max_tiles_on_map.y + 0.1;
		data->menu.update = true;
	}
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_UP) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_W))
	{
		data->menu.map_offset.y -= MAP_TRANSLATE_SPEED;
		if (data->menu.map_offset.y < -.4)
			data->menu.map_offset.y = -.4;
		data->menu.update = true;
	}
}

void	menu_loop(void *v_data)
{
	t_data			*data;
	t_vector_int	pos;

	data = (t_data *)v_data;
	if (data->menu.update)
	{
		if (data->menu.menu_level == 0)
		{
			pos.x = MENU_CURSOR_0_X_POS * data->hud.scale;
			pos.y = (MENU_CURSOR_0_Y_START * data->hud.scale) + \
					MENU_CURSOR_0_JUMP * data->menu.cursor_pos * \
					data->hud.scale;
			draw_menu_screen(data, data->mlx.menu_screen);
		}
		else if (data->menu.menu_level == 1)
		{
			pos.x = MENU_CURSOR_1_X_POS * data->hud.scale;
			pos.y = (MENU_CURSOR_1_Y_START * data->hud.scale) + \
					MENU_CURSOR_1_JUMP * \
					data->menu.cursor_pos * data->hud.scale;
			draw_menu_screen(data, data->mlx.level_select);
		}
		else if (data->menu.menu_level == 2)
		{
			pos.x = MENU_CURSOR_1_X_POS * data->hud.scale;
			pos.y = (MENU_CURSOR_1_Y_START * data->hud.scale) + \
					MENU_CURSOR_1_JUMP * \
					data->menu.cursor_pos * data->hud.scale;
			draw_menu_screen(data, data->mlx.map_editor_screen);
			mlx_set_cursor_mode(data->mlx.mlx_handle, MLX_MOUSE_NORMAL);
			data->menu.cursor = false;
			if (data->menu.enemy_btn.active == true)
				draw_check_mark(data, data->menu.enemy_btn.rect.pos0);
			if (data->menu.floor_btn.active == true)
				draw_check_mark(data, data->menu.floor_btn.rect.pos0);
			if (data->menu.obj_btn.active == true)
				draw_check_mark(data, data->menu.obj_btn.rect.pos0);
			draw_map_editor(data);
		}
		if (data->menu.cursor)
			draw_cursor(data, pos);
		data->menu.update = false;
	}
	if (data->menu.menu_level == 2)
		move_map(data);
}
