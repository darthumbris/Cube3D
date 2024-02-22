/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 11:53:16 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/29 10:58:01 by shoogenb      ########   odam.nl         */
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

void	draw_icon_square(t_mlx *mlx, t_vector_int offset, int tile_plane[2], \
						t_map_edit *editor)
{
	int					plane;
	t_vector_int		icon;
	mlx_texture_t		*atlas;
	int					wh[2];

	icon = get_icon_pos(&editor->sprt_drops, tile_plane[0], tile_plane[1]);
	plane = get_plane(tile_plane[0], tile_plane[1]);
	atlas = get_icon_texture(mlx, plane);
	wh[0] = 16;
	wh[1] = 16;
	draw_texture_area(mlx->menu_editor, atlas, offset, icon, wh, \
						editor->map_zoom);
}

static void	draw_map_area(t_data *data, t_map_edit *editor, double scale)
{
	t_rect			grid;
	const double	scale_grid = scale / editor->grid_size;

	grid.pos0.x = 0;
	grid.pos0.y = 0;
	editor->grid_size = GRID_SIZE * scale * editor->map_zoom + 1;
	grid.pos1.x = editor->grid_size;
	grid.pos1.y = editor->grid_size;
	editor->max_tiles_on_map.x = 213 * scale_grid - 1;
	editor->max_tiles_on_map.y = 218 * scale_grid - 1;
	draw_map_tiles(data, &data->menu.editor);
	draw_map_grid(data, grid, &data->menu.editor);
}

void	draw_map_editor(t_data *data)
{
	draw_map_area(data, &data->menu.editor, data->hud.scale);
	draw_drop_down_lsts(&data->mlx, &data->menu.editor);
	draw_buttons(&data->mlx, &data->menu.editor);
}
