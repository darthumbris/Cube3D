/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_mouse_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 08:58:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/13 16:59:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static t_vector_int	get_map_pos(t_menu *menu, t_vector_int pos)
{
	t_vector_int	map;

	map.x = ((100 * (pos.x - menu->map_area.pos0.x) / menu->grid_size) \
				+ 100 * menu->map_offset.x) / 100;
	map.y = ((100 * (pos.y - menu->map_area.pos0.y) / menu->grid_size) \
				+ 100 * menu->map_offset.y) / 100;
	return (map);
}

static int	get_correct_plane(int active_plane)
{
	if (active_plane == 0 || active_plane == 1)
		return (0);
	else if (active_plane == 2 || active_plane == 3)
		return (1);
	return (2);
}

static uint8_t	get_tile_value(int plane, int dir, int difficulty, int sprt)
{
	const int	tile_shift = difficulty * 3 + dir;

	if (plane == 0 && wall_icon_lst[sprt].tile_value_begin + tile_shift <= \
		wall_icon_lst[sprt].tile_value_end)
		return (wall_icon_lst[sprt].tile_value_begin + tile_shift);
	else if (plane == 1)
		return (zone_icon_lst[sprt].tile_value_begin);
	else if (plane == 2)
		return (obj_icon_lst[sprt].tile_value_begin);
	else if (plane == 3)
		return (item_icon_lst[sprt].tile_value_begin);
	else if (enemy_icon_lst[sprt].tile_value_begin + tile_shift <= \
		enemy_icon_lst[sprt].tile_value_end)
		return (enemy_icon_lst[sprt].tile_value_begin + tile_shift);
	return (0);
}

//TODO also possible to place on floors 
//(0 should be replaced by is_floor function)
//TODO also make that you can't place a wall when there is already
// an obj or enmy
static void	change_map(mouse_key_t button, t_menu *menu, t_vector_int map)
{
	if (button == MLX_MOUSE_BUTTON_LEFT && \
		menu->map[map.y][map.x][menu->active_plane] != menu->active_sprite)
	{
		// if (!menu->active_plane)
			menu->map[map.y][map.x][get_correct_plane(menu->active_plane)] = \
			get_tile_value(menu->active_plane, 0, 0, menu->active_sprite - 1);
	}
	else if (button == MLX_MOUSE_BUTTON_RIGHT)
		menu->map[map.y][map.x][get_correct_plane(menu->active_plane)] = 0;
}

void	menu_mouse_handler(mouse_key_t button, action_t action, \
		modifier_key_t mods, void *param)
{
	t_vector_int	pos;
	t_vector_int	map;
	t_data			*data;
	t_menu			*menu;

	(void)mods;
	data = (t_data *)param;
	if (data->menu.menu_level != 2)
		return ;
	menu = &data->menu;
	menu->update = true;
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	map = get_map_pos(menu, pos);
	if (map.x > 0 && map.y > 0 && map.x < MAX_MAP_SIZE && map.y < MAX_MAP_SIZE \
		&& is_mouse_in_rect(pos.x, pos.y, menu->map_area))
		change_map(button, menu, map);
	check_btns_clicked(data, button, action, pos);
}
