/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 11:53:16 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/07 17:42:07 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	is_in_map_area(t_rect map, int x, int y)
{
	return (x > map.pos0.x && y > map.pos0.y && \
			x < map.pos1.x && y < map.pos1.y);
}

static void	draw_grid_square(t_data *data, t_rect rec, uint32_t c, \
	t_vector_int offset)
{
	uint8_t	*map;
	int		y;
	int		x;

	y = rec.pos0.y + offset.y;
	map = data->mlx.fg->pixels;
	if (y < 0)
		y = 0;
	while (y < rec.pos1.y + offset.y && y < (int)data->mlx.fg->height)
	{
		x = rec.pos1.x + offset.x;
		if (is_in_map_area(data->menu.map_area, x, y))
			*(uint32_t *)(map + ((y * data->mlx.fg->width + x) * 4)) = c;
		x = rec.pos0.x + offset.x;
		if (is_in_map_area(data->menu.map_area, x, y))
			*(uint32_t *)(map + ((y * data->mlx.fg->width + x) * 4)) = c;
		y++;
	}
	x = rec.pos0.x + offset.x;
	if (x < 0)
		x = 0;
	while (x < rec.pos1.x + offset.x && x < (int)data->mlx.fg->width)
	{
		y = rec.pos0.y + offset.y;
		if (is_in_map_area(data->menu.map_area, x, y))
			*(uint32_t *)(map + ((y * data->mlx.fg->width + x) * 4)) = c;
		y = rec.pos1.y + offset.y;
		if (is_in_map_area(data->menu.map_area, x, y))
			*(uint32_t *)(map + ((y * data->mlx.fg->width + x) * 4)) = c;
		x++;
	}
}

static void	draw_filled_square(t_data *data, t_rect rec, t_vector_int offset, int tile)
{
	const uint32_t	color = get_color_tile(tile);
	uint8_t			*map;
	int				y;
	int				x;

	rec.pos0.x += 2;
	rec.pos0.y += 2;
	rec.pos1.x -= 1;
	rec.pos1.y -= 1;
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
				*(uint32_t *)(map + ((y * data->mlx.fg->width + x) * 4)) = color;
			x++;
		}
		y++;
	}
}

static bool	is_border_map(t_vector_int map_pos)
{
	return (map_pos.x == 0 || map_pos.y == 0 || \
	map_pos.x == MAX_MAP_SIZE - 1 || map_pos.y == MAX_MAP_SIZE - 1);
}

void	draw_map_grid(t_data *data, t_rect grid)
{
	t_vector_int	map_pos;
	t_vector_int	pix;

	map_pos.y = (int)data->menu.map_offset.y;
	while (map_pos.y < MAX_MAP_SIZE && \
		map_pos.y < data->menu.map_offset.y + data->menu.max_tiles_on_map.y + 1)
	{
		map_pos.x = (int)data->menu.map_offset.x;
		while (map_pos.x < MAX_MAP_SIZE && \
			map_pos.x < data->menu.map_offset.x + data->menu.max_tiles_on_map.x + 1)
		{
			pix.x = (map_pos.x - data->menu.map_offset.x) * \
				data->menu.grid_size + data->menu.map_area.pos0.x;
			pix.y = (map_pos.y - data->menu.map_offset.y) * \
				data->menu.grid_size + data->menu.map_area.pos0.y;
			draw_grid_square(data, grid, WALL_COLOUR, pix);
			if (is_border_map(map_pos))
				draw_grid_square(data, grid, MAP_BORDER_COLOUR, pix);
			map_pos.x++;
		}
		map_pos.y++;
	}
}

void	draw_map_tiles(t_data *data, t_rect grid)
{
	t_vector_int	map_pos;
	t_vector_int	pix;

	map_pos.y = (int)data->menu.map_offset.y;
	while (map_pos.y < MAX_MAP_SIZE && \
		map_pos.y < data->menu.map_offset.y + data->menu.max_tiles_on_map.y + 1)
	{
		map_pos.x = (int)data->menu.map_offset.x;
		while (map_pos.x < MAX_MAP_SIZE && \
			map_pos.x < data->menu.map_offset.x + data->menu.max_tiles_on_map.x + 1)
		{
			pix.x = (map_pos.x - data->menu.map_offset.x) * \
				data->menu.grid_size + data->menu.map_area.pos0.x;
			pix.y = (map_pos.y - data->menu.map_offset.y) * \
				data->menu.grid_size + data->menu.map_area.pos0.y;
			if (data->menu.enemy_btn.active == true && data->menu.map[map_pos.y][map_pos.x][2] != 0)
				draw_filled_square(data, grid, pix, data->menu.map[map_pos.y][map_pos.x][2]);
			if (data->menu.obj_btn.active == true && data->menu.map[map_pos.y][map_pos.x][1] != 0)
				draw_filled_square(data, grid, pix, data->menu.map[map_pos.y][map_pos.x][1]);
			if (data->menu.floor_btn.active == true && data->menu.map[map_pos.y][map_pos.x][0] != 0)
				draw_filled_square(data, grid, pix, data->menu.map[map_pos.y][map_pos.x][0]);
			map_pos.x++;
		}
		map_pos.y++;
	}
}

static void	draw_map_area(t_data *data)
{
	t_rect			grid;

	grid.pos0.x = 0;
	grid.pos0.y = 0;
	data->menu.grid_size = GRID_SIZE * data->hud.scale * data->menu.map_zoom;
	grid.pos1.x = data->menu.grid_size;
	grid.pos1.y = data->menu.grid_size;
	data->menu.max_tiles_on_map.x = 213 * data->hud.scale / data->menu.grid_size - 1;
	data->menu.max_tiles_on_map.y = 218 * data->hud.scale / data->menu.grid_size - 1;
	draw_map_grid(data, grid);
	draw_map_tiles(data, grid);
}

void	draw_map_editor(t_data *data)
{
	draw_map_area(data);
	draw_drop_down_lsts(data);
	draw_buttons(data);
	//draw_tiles(data);
}
