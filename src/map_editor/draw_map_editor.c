/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 11:53:16 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 14:45:01 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_in_map_area(t_rect map, int x, int y)
{
	return (x > map.pos0.x && y > map.pos0.y && \
			x < map.pos1.x && y < map.pos1.y);
}

void	draw_icon_square(t_data *data, t_vector_int offset, int tile_plane[2])
{
	const t_vector_int	icon = get_icon_pos(data, tile_plane[0], tile_plane[1]);
	uint8_t				*map;
	uint8_t				*atlas;
	t_vector_int		pixel;
	t_vector_int		tex;

	pixel.x = -1;
	atlas = data->mlx.wall_icons->pixels;
	while (++pixel.x < data->menu.grid_size - 1)
	{
		tex.x = (pixel.x / data->menu.map_zoom) + (icon.x * 16);
		map = data->mlx.fg->pixels + ((pixel.x + 1 + offset.x + \
			(offset.y + data->menu.grid_size - 2) * data->mlx.fg->width) * 4);
		pixel.y = data->menu.grid_size - 1;
		while (--pixel.y > 0)
		{
			tex.y = (pixel.y / data->menu.map_zoom) + (icon.y * 16);
			if (is_in_map_area(data->menu.map_area, pixel.x + \
								offset.x, pixel.y + offset.y))
				*(uint32_t *)map = (*(int *)(atlas + ((tex.y * \
					data->mlx.wall_icons->width + tex.x) * 4)));
			map -= data->floor.width4;
		}
	}
}

static void	draw_map_area(t_data *data)
{
	t_rect			grid;
	const double	scale_grid = data->hud.scale / data->menu.grid_size;

	grid.pos0.x = 0;
	grid.pos0.y = 0;
	data->menu.grid_size = GRID_SIZE * data->hud.scale * data->menu.map_zoom + 1;
	grid.pos1.x = data->menu.grid_size;
	grid.pos1.y = data->menu.grid_size;
	data->menu.max_tiles_on_map.x = 213 * scale_grid - 1;
	data->menu.max_tiles_on_map.y = 218 * scale_grid - 1;
	draw_map_grid(data, grid, &data->menu);
	draw_map_tiles(data, &data->menu);
}

void	draw_map_editor(t_data *data)
{
	draw_map_area(data);
	draw_drop_down_lsts(data);
	draw_buttons(data);
}
