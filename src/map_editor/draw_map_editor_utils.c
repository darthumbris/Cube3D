/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 09:58:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/10 13:38:14 by shoogenb      ########   odam.nl         */
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

t_vector_int	get_icon_pos(t_data *data, int tile, int plane)
{
	if (plane == 0)
		return (data->menu.wall_ddlst.btn_lst[tile - 1].icon_pos);
	else if (plane == 1)
		return (data->menu.decor_ddlst.btn_lst[tile - 1].icon_pos);
	else
		return (data->menu.enemy_ddlst.btn_lst[tile - 1].icon_pos);
}

static void	draw_active_plane_tile(t_data *data, t_menu *menu, \
									t_vector_int pos[2])
{
	t_vector_int	m;
	t_vector_int	pix;
	int				tile_plane[2];

	pix = pos[0];
	m = pos[1];
	if (menu->enemy_btn.active && menu->map[m.y][m.x][2] != 0)
	{
		tile_plane[0] = menu->map[m.y][m.x][2];
		tile_plane[1] = 2;
		draw_icon_square(data, pix, tile_plane);
	}
	if (menu->obj_btn.active && menu->map[m.y][m.x][1] != 0)
	{
		tile_plane[0] = menu->map[m.y][m.x][1];
		tile_plane[1] = 1;
		draw_icon_square(data, pix, tile_plane);
	}
	if (menu->floor_btn.active && menu->map[m.y][m.x][0] != 0)
	{
		tile_plane[0] = menu->map[m.y][m.x][0];
		tile_plane[1] = 0;
		draw_icon_square(data, pix, tile_plane);
	}
}

void	draw_map_tiles(t_data *data, t_menu *menu)
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
			draw_active_plane_tile(data, &data->menu, pos);
			map_pos.x++;
		}
		map_pos.y++;
	}
}
