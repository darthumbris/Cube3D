/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 11:53:16 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/08 14:54:20 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_in_map_area(t_rect map, int x, int y)
{
	return (x > map.pos0.x && y > map.pos0.y && \
			x < map.pos1.x && y < map.pos1.y);
}

static void	make_smaller_square(t_rect *rec)
{
	rec->pos0.x += 1;
	rec->pos0.y += 1;
}

void	draw_filled_square(t_data *data, t_rect rec, \
							t_vector_int offset, int tile)
{
	const uint32_t	c = get_color_tile(tile);
	uint8_t			*map;
	int				y;
	int				x;

	make_smaller_square(&rec);
	y = rec.pos0.y + offset.y;
	map = data->mlx.fg->pixels;
	if (y < 0)
		y = 0;
	while (y < rec.pos1.y + offset.y && y < (int)data->mlx.fg->height)
	{
		x = rec.pos0.x + offset.x;
		if (x < 0)
			x = 0;
		while (x < rec.pos1.x + offset.x && x < (int)data->mlx.fg->width)
		{
			if (is_in_map_area(data->menu.map_area, x, y))
				*(uint32_t *)(map + ((y * data->mlx.fg->width + x) * 4)) = c;
			x++;
		}
		y++;
	}
}

static void	draw_map_area(t_data *data)
{
	t_rect			grid;
	const double	scale_grid = data->hud.scale / data->menu.grid_size;

	grid.pos0.x = 0;
	grid.pos0.y = 0;
	data->menu.grid_size = GRID_SIZE * data->hud.scale * data->menu.map_zoom;
	grid.pos1.x = data->menu.grid_size;
	grid.pos1.y = data->menu.grid_size;
	data->menu.max_tiles_on_map.x = 213 * scale_grid - 1;
	data->menu.max_tiles_on_map.y = 218 * scale_grid - 1;
	draw_map_grid(data, grid, &data->menu);
	draw_map_tiles(data, grid, &data->menu);
}

void	draw_map_editor(t_data *data)
{
	draw_map_area(data);
	draw_drop_down_lsts(data);
	draw_buttons(data);
	//draw_tiles(data);
}
