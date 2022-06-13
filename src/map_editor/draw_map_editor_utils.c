/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 09:58:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/13 15:10:05 by shoogenb      ########   odam.nl         */
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

t_vector_int	icon_lst_check(t_ddlst *drop, int tile, const t_icon icon_lst[])
{
	uint32_t	i;

	i = 0;
	while (i < drop->elements)
	{
		if (icon_lst[i].tile_value_begin >= tile && \
			tile <= icon_lst[i].tile_value_end)
			return (drop->btn_lst[i].icon_pos);
		i++;
	}
	return ((t_vector_int){0, 0});
}

t_vector_int	get_icon_pos(t_data *data, int tile, int plane)
{
	t_vector_int	pos;

	if (plane == 0)
	{
		if (is_wall_lst(tile))
		{
			pos = icon_lst_check
				(&data->menu.wall_ddlst, tile, wall_icon_lst);
			// printf("printing wall\n");
			// printf("tile: %d, icon_pos: %d, %d\n", tile, pos.y, pos.x);
			return (icon_lst_check
				(&data->menu.wall_ddlst, tile, wall_icon_lst));
		}
		return (icon_lst_check(&data->menu.zone_ddlst, tile, zone_icon_lst));
	}
	else if (plane == 1)
	{
		if (is_decor_lst(tile))
			return (icon_lst_check
				(&data->menu.decor_ddlst, tile, obj_icon_lst));
		return (icon_lst_check(&data->menu.item_ddlst, tile, item_icon_lst));
	}
	else
		return (icon_lst_check(&data->menu.enemy_ddlst, tile, enemy_icon_lst));
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
