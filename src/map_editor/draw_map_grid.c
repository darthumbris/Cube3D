/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_grid.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:49:18 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/08 15:00:52 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	is_border_map(t_vector_int map_pos)
{
	return (map_pos.x == 0 || map_pos.y == 0 || \
	map_pos.x == MAX_MAP_SIZE - 1 || map_pos.y == MAX_MAP_SIZE - 1);
}

static void	draw_grid_horizontal_line(t_data *data, t_rect rec, \
								uint32_t c, t_vector_int offset)
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
}

static void	draw_grid_square(t_data *data, t_rect rec, uint32_t c, \
	t_vector_int offset)
{
	uint8_t	*map;
	int		y;
	int		x;

	draw_grid_horizontal_line(data, rec, c, offset);
	map = data->mlx.fg->pixels;
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

void	draw_map_grid(t_data *data, t_rect grid, t_menu *menu)
{
	t_vector_int	map_pos;
	t_vector_int	pix;

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
			draw_grid_square(data, grid, WALL_COLOUR, pix);
			if (is_border_map(map_pos))
				draw_grid_square(data, grid, MAP_BORDER_COLOUR, pix);
			map_pos.x++;
		}
		map_pos.y++;
	}
}
