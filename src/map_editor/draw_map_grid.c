/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_grid.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:49:18 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 12:36:08 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	is_border_map(t_vector_int map_pos)
{
	return (map_pos.x == 0 || map_pos.y == 0 || \
	map_pos.x == MAX_MAP_SIZE - 1 || map_pos.y == MAX_MAP_SIZE - 1);
}

static void	draw_grid_square(t_data *data, t_rect rec, uint32_t c, \
	t_vector_int ofs)
{
	uint8_t			*map;
	t_vector_int	pos;
	const t_rect	map_area = data->menu.editor.map_area;

	map = data->mlx.menu_editor->pixels;
	pos.x = rec.pos0.x + ofs.x;
	if (pos.x < -1)
		pos.x = -1;
	while (++pos.x < rec.pos1.x + ofs.x && pos.x < (int)data->mlx.fg->width)
	{
		if (is_in_map_area(map_area, pos.x, rec.pos0.y + ofs.y))
			*(uint32_t *)(map + (((rec.pos0.y + ofs.y) * SCREEN_WIDTH + pos.x) * 4)) = c;
		if (is_in_map_area(map_area, pos.x, rec.pos1.y + ofs.y))
			*(uint32_t *)(map + (((rec.pos1.y + ofs.y) * SCREEN_WIDTH + pos.x) * 4)) = c;
	}
	pos.y = rec.pos0.y + ofs.y - 1;
	if (pos.y < -1)
		pos.y = -1;
	while (++pos.y < rec.pos1.y + ofs.y && pos.y < (int)data->mlx.fg->height)
	{
		if (is_in_map_area(map_area, rec.pos1.x + ofs.x, pos.y))
			*(uint32_t *)(map + ((pos.y * SCREEN_WIDTH + rec.pos1.x + ofs.x) * 4)) = c;
		if (is_in_map_area(map_area, rec.pos0.x + ofs.x, pos.y))
			*(uint32_t *)(map + ((pos.y * SCREEN_WIDTH + rec.pos0.x + ofs.x) * 4)) = c;
	}
}

void	draw_map_grid(t_data *data, t_rect grid, t_map_edit *editor)
{
	t_vector_int	map_pos;
	t_vector_int	pix;

	map_pos.y = (int)editor->map_offset.y;
	while (map_pos.y < MAX_MAP_SIZE && \
		map_pos.y < editor->map_offset.y + editor->max_tiles_on_map.y + 1)
	{
		map_pos.x = (int)editor->map_offset.x;
		while (map_pos.x < MAX_MAP_SIZE && \
			map_pos.x < editor->map_offset.x + editor->max_tiles_on_map.x + 1)
		{
			pix.x = (map_pos.x - editor->map_offset.x) * \
				editor->grid_size + editor->map_area.pos0.x;
			pix.y = (map_pos.y - editor->map_offset.y) * \
				editor->grid_size + editor->map_area.pos0.y;
			draw_grid_square(data, grid, WALL_COLOUR, pix);
			if (is_border_map(map_pos))
				draw_grid_square(data, grid, MAP_BORDER_COLOUR, pix);
			map_pos.x++;
		}
		map_pos.y++;
	}
}
