/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_mouse_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 08:58:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 14:22:40 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
	map.x = ((pos.x - menu->map_area.pos0.x) / menu->grid_size) \
				+ menu->map_offset.x;
	map.y = ((pos.y - menu->map_area.pos0.y) / menu->grid_size) \
				+ menu->map_offset.y;
	if (map.x > 0 && map.y > 0 && map.x < MAX_MAP_SIZE && map.y < MAX_MAP_SIZE \
		&& is_mouse_in_rect(pos.x, pos.y, menu->map_area))
	{
		if (button == MLX_MOUSE_BUTTON_LEFT && \
			menu->map[map.y][map.x][menu->active_plane] != menu->active_sprite)
			menu->map[map.y][map.x][menu->active_plane] = menu->active_sprite;
		else if (button == MLX_MOUSE_BUTTON_RIGHT)
			menu->map[map.y][map.x][menu->active_plane] = 0;
	}
	check_btns_clicked(data, button, action, pos);
}
