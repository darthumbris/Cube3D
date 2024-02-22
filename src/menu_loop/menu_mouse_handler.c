/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_mouse_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 08:58:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/29 11:00:48 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static t_vector_int	get_map_pos(t_map_edit *editor, t_vector_int pos)
{
	t_vector_int	map;

	map.x = ((100 * (pos.x - editor->map_area.pos0.x) / editor->grid_size) \
				+ 100 * editor->map_offset.x) / 100;
	map.y = ((100 * (pos.y - editor->map_area.pos0.y) / editor->grid_size) \
				+ 100 * editor->map_offset.y) / 100;
	return (map);
}

static int	get_correct_plane(int active_plane)
{
	if (active_plane == 0 || active_plane == 1)
		return (0);
	else if (active_plane == 2 || active_plane == 3)
		return (1);
	return (2);
}

static uint8_t	get_tile_value(int plane, int dir, int difficulty, int sprt)
{
	const int	tile_shift = difficulty * 4 + dir;

	if (plane == 0 && wall_icon_lst[sprt].tile_value_begin + tile_shift <= \
		wall_icon_lst[sprt].tile_value_end)
		return (wall_icon_lst[sprt].tile_value_begin + tile_shift);
	else if (plane == 1)
		return (zone_icon_lst[sprt].tile_value_begin);
	else if (plane == 2)
		return (obj_icon_lst[sprt].tile_value_begin);
	else if (plane == 3)
		return (item_icon_lst[sprt].tile_value_begin);
	else if (enemy_icon_lst[sprt].tile_value_begin + tile_shift <= \
		enemy_icon_lst[sprt].tile_value_end)
		return (enemy_icon_lst[sprt].tile_value_begin + tile_shift);
	return (0);
}

//TODO check if this is the same as in the other places for direction
static int	get_dir_editor(t_map_edit *edit)
{
	char	*txt;

	if (edit->active_plane != 4)
		return (0);
	txt = edit->sp_drops.drop[0].active.txt;
	if (ft_strcmp(txt, "north") == 0)
		return (0);
	else if (ft_strcmp(txt, "east") == 0)
		return (1);
	else if (ft_strcmp(txt, "south") == 0)
		return (2);
	return (3);
}

static int	get_difficulty_editor(t_map_edit *edit, int active_sprite)
{
	char	*txt;

	if (edit->active_plane != 4 || active_sprite < 3)
		return (0);
	txt = edit->sp_drops.drop[1].active.txt;
	if (ft_strcmp(txt, "easy") == 0)
		return (0);
	else if (ft_strcmp(txt, "medium") == 0)
		return (1);
	return (2);
}

static int	get_active_sprt(t_map_edit *edit)
{
	int			i;
	int			plane;
	t_button	*btn_lst;
	char		*actv;

	plane = edit->active_plane;
	btn_lst = edit->sprt_drops.drop[plane].btn_lst;
	actv = edit->sprt_drops.drop[plane].active.txt;
	i = -1;
	while (++i < (int)edit->sprt_drops.drop[plane].elements)
	{
		if (ft_strcmp(btn_lst[i].txt, actv) == 0)
			return (i + 1);
	}
	return (0);
}

//TODO also possible to place on floors 
//(0 should be replaced by is_floor function)
//TODO also make that you can't place a wall when there is already
// an obj or enmy
static void	change_map(mouse_key_t btn, t_map_edit *edit, t_vector_int map)
{
	int	dir;
	int	diff;
	int	plane;
	int	actv;

	dir = get_dir_editor(edit);
	plane = get_correct_plane(edit->active_plane);
	actv = get_active_sprt(edit);
	diff = get_difficulty_editor(edit, actv);
	if (btn == MLX_MOUSE_BUTTON_LEFT && \
		edit->map[map.y][map.x][edit->active_plane] != actv)
	{
		edit->map[map.y][map.x][plane] = \
		get_tile_value(edit->active_plane, dir, diff, actv - 1);
	}
	else if (btn == MLX_MOUSE_BUTTON_RIGHT)
		edit->map[map.y][map.x][plane] = 0;
}

void	menu_mouse_handler(mouse_key_t button, action_t action, \
		modifier_key_t mods, void *param)
{
	t_vector_int	pos;
	t_vector_int	map;
	t_data			*data;
	t_menu			*menu;

	(void)mods;
	data = (t_data *)param;
	if (data->menu.menu_level != 2 || data->menu.editor.file.save_btn.active)
		return ;
	menu = &data->menu;
	menu->update = true;
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	map = get_map_pos(&menu->editor, pos);
	if (map.x > 0 && map.y > 0 && map.x < MAX_MAP_SIZE && map.y < MAX_MAP_SIZE \
		&& is_mouse_in_rect(pos.x, pos.y, menu->editor.map_area))
		change_map(button, &menu->editor, map);
	check_btns_clicked(data, button, action, pos);
}
