/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 09:58:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 12:24:40 by shoogenb      ########   odam.nl         */
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
	t_vector_int	pos;

	if (plane == 0)
	{
		if (is_wall_lst(tile))
		{
			pos = icon_lst_check
				(&sprt->wall_ddlst, tile, wall_icon_lst);
			return (icon_lst_check
				(&sprt->wall_ddlst, tile, wall_icon_lst));
		}
		return (icon_lst_check(&sprt->zone_ddlst, tile, zone_icon_lst));
	}
	else if (plane == 1)
	{
		if (is_decor_lst(tile))
			return (icon_lst_check
				(&sprt->decor_ddlst, tile, obj_icon_lst));
		return (icon_lst_check(&sprt->item_ddlst, tile, item_icon_lst));
	}
	else
		return (icon_lst_check(&sprt->enemy_ddlst, tile, enemy_icon_lst));
}

static void	draw_active_plane_tile(t_data *data, t_map_edit *editor, \
									t_vector_int pos[2])
{
	t_vector_int	m;
	t_vector_int	pix;
	int				tile_plane[2];

	pix = pos[0];
	m = pos[1];
	if (editor->vis_btns.floor_btn.active && editor->map[m.y][m.x][0] != 0)
	{
		tile_plane[0] = editor->map[m.y][m.x][0];
		tile_plane[1] = 0;
		draw_icon_square(&data->mlx, pix, tile_plane, &data->menu.editor);
	}
	if (editor->vis_btns.obj_btn.active && editor->map[m.y][m.x][1] != 0)
	{
		tile_plane[0] = editor->map[m.y][m.x][1];
		tile_plane[1] = 1;
		draw_icon_square(&data->mlx, pix, tile_plane, &data->menu.editor);
	}
	if (editor->vis_btns.enemy_btn.active && editor->map[m.y][m.x][2] != 0)
	{
		tile_plane[0] = editor->map[m.y][m.x][2];
		tile_plane[1] = 2;
		draw_icon_square(&data->mlx, pix, tile_plane, &data->menu.editor);
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
