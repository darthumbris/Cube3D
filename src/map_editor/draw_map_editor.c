/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 11:53:16 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/13 16:54:04 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_in_map_area(t_rect map, int x, int y)
{
	return (x > map.pos0.x && y > map.pos0.y && \
			x < map.pos1.x && y < map.pos1.y);
}

static int	get_plane(int tile, int plane)
{
	if (plane == 0)
	{
		if (is_wall_lst(tile))
			return (0);
		return (1);
	}
	else if (plane == 1)
	{
		if (is_decor_lst(tile))
			return (2);
		return (3);
	}
	return (4);
}

void	draw_icon_square(t_data *data, t_vector_int offset, int tile_plane[2])
{
	int					plane;
	const t_vector_int	icon = get_icon_pos(data, tile_plane[0], tile_plane[1]);
	mlx_texture_t		*atlas;
	int					wh[2];

	plane = get_plane(tile_plane[0], tile_plane[1]);
	atlas = get_icon_texture(data, plane);
	wh[0] = 16;
	wh[1] = 16;
	draw_texture_area(data->mlx.menu_editor, atlas, offset, icon, wh, \
						data->menu.map_zoom);
}

static void	draw_map_area(t_data *data)
{
	t_rect			grid;
	const double	scale_grid = data->hud.scale / data->menu.grid_size;

	grid.pos0.x = 0;
	grid.pos0.y = 0;
	data->menu.grid_size = GRID_SIZE * data->hud.scale * \
							data->menu.map_zoom + 1;
	grid.pos1.x = data->menu.grid_size;
	grid.pos1.y = data->menu.grid_size;
	data->menu.max_tiles_on_map.x = 213 * scale_grid - 1;
	data->menu.max_tiles_on_map.y = 218 * scale_grid - 1;
	draw_map_tiles(data, &data->menu);
	draw_map_grid(data, grid, &data->menu);
}

void	draw_map_editor(t_data *data)
{
	draw_map_area(data);
	draw_drop_down_lsts(data);
	draw_buttons(data);
}
