/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_loop_editor.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:54:45 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/30 15:25:01 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	is_movement_key_down(mlx_t *mlx)
{
	return (mlx_is_key_down(mlx, MLX_KEY_LEFT) || \
			mlx_is_key_down(mlx, MLX_KEY_RIGHT) || \
			mlx_is_key_down(mlx, MLX_KEY_UP) || \
			mlx_is_key_down(mlx, MLX_KEY_DOWN) || \
			mlx_is_key_down(mlx, MLX_KEY_W) || \
			mlx_is_key_down(mlx, MLX_KEY_S) || \
			mlx_is_key_down(mlx, MLX_KEY_D) || \
			mlx_is_key_down(mlx, MLX_KEY_A));
}

void	move_map(mlx_t *mlx, t_menu *menu, t_vector_double *map_offset, t_vector_int max_tiles)
{
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || \
		mlx_is_key_down(mlx, MLX_KEY_A))
		map_offset->x -= MAP_TRANSLATE_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || \
		mlx_is_key_down(mlx, MLX_KEY_D))
		map_offset->x += MAP_TRANSLATE_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || \
		mlx_is_key_down(mlx, MLX_KEY_S))
		map_offset->y += MAP_TRANSLATE_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || \
		mlx_is_key_down(mlx, MLX_KEY_W))
		map_offset->y -= MAP_TRANSLATE_SPEED;
	if (is_movement_key_down(mlx))
		menu->update = true;
	if (map_offset->x < -.4)
		map_offset->x = -.4;
	if (map_offset->x > MAX_MAP_SIZE - max_tiles.x - 0.4)
		map_offset->x = MAX_MAP_SIZE - max_tiles.x - 0.4;
	if (map_offset->y > MAX_MAP_SIZE - max_tiles.y - 0.4)
			map_offset->y = MAX_MAP_SIZE - max_tiles.y - 0.4;
	if (map_offset->y < -.4)
		map_offset->y = -.4;
}

static bool	is_vis_btns_hvr(t_vis_btns *vis_btns, int x, int y)
{
	int	i;

	i = -1;
	while (++i < DIS_BTNS)
	{
		if (is_hover(&vis_btns->btns[i], x, y))
			return (true);
	}
	return (false);
}

static bool	is_pnt_btns_hvr(t_pnt_btns *pnt, int x, int y)
{
	int	i;

	i = -1;
	while (++i < PNT_BTNS)
	{
		if (is_hover(&pnt->btns[i], x, y))
			return (true);
	}
	return (false);
}

static bool	is_file_btn_hvr(t_file *file, int x, int y)
{
	return (is_hover(&file->load_btn, x, y) || \
			is_hover(&file->save_btn, x, y));
}

static bool	is_drop_lst_hover(t_map_edit *editor, int x, int y)
{
	int		i;

	if (is_hover(&editor->plane_ddlst.active, x, y))
		return (true);
	i = -1;
	while (++i < SPRITE_LSTS)
	{
		if (is_hover(&editor->sprt_drops.drop[i].active, x, y))
			return (true);
	}
	if (editor->sp_drops.drop[ROTATION].active.active == false && \
		(is_hover(&editor->sp_drops.drop[DIFFICULTY].active, x, y) || \
		is_hover(&editor->sp_drops.drop[ROTATION].active, x, y)))
		return (true);
	if (editor->plane_ddlst.active.active && \
		is_mouse_in_rect(x, y, editor->plane_ddlst.open_rct))
		return (true);
	i = -1;
	while (++i < SPRITE_LSTS)
	{
		if (editor->sprt_drops.drop[i].active.active && \
			is_mouse_in_rect(x, y, editor->sprt_drops.drop[i].open_rct))
			return (true);
		if (i < SPECIAL_LSTS && editor->sp_drops.drop[i].active.active && \
			is_mouse_in_rect(x, y, editor->sp_drops.drop[i].open_rct))
			return (true);
	}
	return (false);
	/* return (is_hover(&editor->plane_ddlst.active, x, y) || \
	// 	is_hover(&editor->sprt_drops.wall_ddlst.active, x, y) || \
	// 	is_hover(&editor->sprt_drops.decor_ddlst.active, x, y) || \
	// 	is_hover(&editor->sprt_drops.enemy_ddlst.active, x, y) || \
	// 	is_hover(&editor->sprt_drops.item_ddlst.active, x, y) || \
	// 	is_hover(&editor->sprt_drops.zone_ddlst.active, x, y) || \
	// 	is_hover(&editor->sp_drops.rotate_ddlst.active, x, y) || \
	// 	(editor->sp_drops.rotate_ddlst.active.active == false && \
	// 	is_hover(&editor->sp_drops.diff_ddlst.active, x, y)) || \
	// 	(editor->plane_ddlst.active.active == true && \
	// 	is_mouse_in_rect(x, y, editor->plane_ddlst.open_rct)) || \
	// 	(editor->sprt_drops.wall_ddlst.active.active == true && \
	// 	is_mouse_in_rect(x, y, editor->sprt_drops.wall_ddlst.open_rct)) || \
	// 	(editor->sp_drops.rotate_ddlst.active.active == true && \
	// 	is_mouse_in_rect(x, y, editor->sp_drops.rotate_ddlst.open_rct)) || \
	// 	(editor->sp_drops.diff_ddlst.active.active == true && \
	// 	is_mouse_in_rect(x, y, editor->sp_drops.diff_ddlst.open_rct)) || \
	// 	(editor->sprt_drops.decor_ddlst.active.active == true && \
	// 	is_mouse_in_rect(x, y, editor->sprt_drops.decor_ddlst.open_rct)) || \
	// 	(editor->sprt_drops.enemy_ddlst.active.active == true && \
	// 	is_mouse_in_rect(x, y, editor->sprt_drops.enemy_ddlst.open_rct)) || \
	// 	(editor->sprt_drops.item_ddlst.active.active == true && \
	// 	is_mouse_in_rect(x, y, editor->sprt_drops.item_ddlst.open_rct)));
	*/
}

void	check_hover(t_data *data)
{
	int			x;
	int			y;
	t_map_edit	*editor;

	editor = &data->menu.editor;
	mlx_get_mouse_pos(data->mlx.mlx_handle, &x, &y);
	if (is_drop_lst_hover(editor, x, y) || \
		is_file_btn_hvr(&editor->file, x, y) || \
		is_pnt_btns_hvr(&editor->pnt_btns, x, y) || \
		is_vis_btns_hvr(&editor->vis_btns, x, y))
		data->menu.update = true;
}
