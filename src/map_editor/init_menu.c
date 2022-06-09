/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_menu.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:23:32 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 12:05:00 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	zero_map(t_data *data)
{
	int	i;
	int	j;
	int	k;

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
}

static bool	init_menu_textures(t_mlx *mlx)
{
	mlx->menu_screen = mlx_load_png("assets/hud/menu_screen.png");
	mlx->level_select = mlx_load_png("assets/hud/level_select.png");
	mlx->cursor = mlx_load_png("assets/hud/selector.png");
	mlx->map_editor_screen = mlx_load_png
		("assets/hud/map_editor_screen.png");
	mlx->check_mark = mlx_load_png("assets/hud/temp_active.png");
	mlx->font = mlx_load_png("assets/hud/font.png");
	mlx->wall_icons = mlx_load_png("assets/hud/wall_textures_icons.png");
	mlx->menu_editor = mlx_new_image
		(mlx->mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (mlx->menu_screen == NULL || mlx->level_select == NULL || \
		mlx->cursor == NULL || mlx->check_mark == NULL || \
		mlx->font == NULL || mlx->wall_icons == NULL)
		return (false);
	return (true);
}

static void	init_map_editor(t_data *data, t_menu *menu)
{
	zero_map(data);
	menu->active_sprite = 1;
	menu->active_plane = 0;
	menu->map_zoom = 2;
	menu->map_offset.x = 149;
	menu->map_offset.y = 149;
	menu->cursor = true;
	menu->cursor_pos = 0;
	menu->menu_level = 0;
	menu->map_area.pos0.x = 103 * data->hud.scale;
	menu->map_area.pos1.x = 315 * data->hud.scale;
	menu->map_area.pos0.y = 15 * data->hud.scale;
	menu->map_area.pos1.y = 232 * data->hud.scale;
	menu->grid_size = GRID_SIZE * data->hud.scale * menu->map_zoom;
	menu->max_tiles_on_map.x = 213 * data->hud.scale / menu->grid_size;
	menu->max_tiles_on_map.y = 218 * data->hud.scale / menu->grid_size;
}

bool	init_menu(t_data *data)
{
	t_vector_int	pos;

	init_hud(data);
	if (init_menu_textures(&data->mlx) == false)
		return (false);
	init_map_editor(data, &data->menu);
	init_buttons(data);
	init_dropdown_lists(&data->menu, data->hud.scale);
	pos.x = MENU_CURSOR_0_X_POS * data->hud.scale;
	pos.y = MENU_CURSOR_0_Y_START * data->hud.scale;
	draw_menu_screen(data, data->mlx.menu_screen);
	draw_cursor(data, pos);
	data->menu.update = false;
	return (true);
}
