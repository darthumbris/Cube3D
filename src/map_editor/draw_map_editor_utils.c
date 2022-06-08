/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 09:58:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/08 15:00:14 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

unsigned int	get_color_tile(int tile)
{
	if (tile == 1)
		return (0x8f8f8fff);
	else if (tile == 2)
		return (0x0000b3ff);
	else if (tile == 3)
		return (0x774e2bff);
	return (0x8f8f8fff);
}

static void	draw_active_plane_tile(t_data *data, t_rect grid, \
								t_menu *menu, t_vector_int pos[2])
{
	t_vector_int	m;
	t_vector_int	pix;

	pix = pos[0];
	m = pos[1];
	if (menu->enemy_btn.active && menu->map[m.y][m.x][2] != 0)
		draw_filled_square(data, grid, pix, data->menu.map[m.y][m.x][2]);
	if (menu->obj_btn.active && menu->map[m.y][m.x][1] != 0)
		draw_filled_square(data, grid, pix, data->menu.map[m.y][m.x][1]);
	if (menu->floor_btn.active && menu->map[m.y][m.x][0] != 0)
		draw_filled_square(data, grid, pix, menu->map[m.y][m.x][0]);
}

void	draw_map_tiles(t_data *data, t_rect grid, t_menu *menu)
{
	t_vector_int	map_pos;
	t_vector_int	pix;
	t_vector_int	pos[2];

	map_pos.y = (int)menu->map_offset.y;
	while (map_pos.y < MAX_MAP_SIZE && \
		map_pos.y < menu->map_offset.y + menu->max_tiles_on_map.y + 1)
	{
		map_pos.x = (int)menu->map_offset.x;
		while (map_pos.x < MAX_MAP_SIZE && \
			map_pos.x < menu->map_offset.x + menu->max_tiles_on_map.x + 1)
		{
			pix.x = (map_pos.x - menu->map_offset.x) * \
				menu->grid_size + menu->map_area.pos0.x;
			pix.y = (map_pos.y - menu->map_offset.y) * \
				menu->grid_size + menu->map_area.pos0.y;
			pos[0] = pix;
			pos[1] = map_pos;
			draw_active_plane_tile(data, grid, &data->menu, pos);
			map_pos.x++;
		}
		map_pos.y++;
	}
}
