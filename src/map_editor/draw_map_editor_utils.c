/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 09:58:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 15:10:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_vector_int	icon_lst_check(t_ddlst *drop, int tile, const t_icon icon_lst[])
{
	uint32_t	i;

	i = 0;
	while (i < drop->elements)
	{
		if (tile >= icon_lst[i].tile_value_begin && \
			tile <= icon_lst[i].tile_value_end)
			return (drop->btn_lst[i].icon_pos);
		i++;
	}
	return ((t_vector_int){0, 0});
}

t_vector_int	get_icon_pos(t_sprt_drop *sprt, int tile, int plane)
{
	if (plane == 0)
	{
		if (is_wall_lst(tile))
			return (icon_lst_check
				(&sprt->drop[WALL], tile, wall_icon_lst));
		return (icon_lst_check(&sprt->drop[ZONE], tile, zone_icon_lst));
	}
	else if (plane == 1)
	{
		if (is_decor_lst(tile))
			return (icon_lst_check
				(&sprt->drop[DECOR], tile, obj_icon_lst));
		return (icon_lst_check(&sprt->drop[ITEM], tile, item_icon_lst));
	}
	else
		return (icon_lst_check(&sprt->drop[ENMY], tile, enemy_icon_lst));
}

static void	draw_active_plane_tile(t_data *data, t_map_edit *editor, \
									t_vector_int pos[2])
{
	t_vector_int	m;
	t_vector_int	pix;
	int				tile_plane[2];
	int				i;

	pix = pos[0];
	m = pos[1];
	i = -1;
	while (++i < DIS_BTNS)
	{
		if (editor->vis_btns.btns[i].active && editor->map[m.y][m.x][i])
		{
			tile_plane[0] = editor->map[m.y][m.x][i];
			tile_plane[1] = i;
			draw_icon_square(&data->mlx, pix, tile_plane, &data->menu.editor);
		}
	}
}

void	draw_map_tiles(t_data *data, t_map_edit *editor)
{
	t_vector_int	map_pos;
	t_vector_int	pix;
	t_vector_int	pos[2];

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
			pos[0] = pix;
			pos[1] = map_pos;
			draw_active_plane_tile(data, editor, pos);
			map_pos.x++;
		}
		map_pos.y++;
	}
}
