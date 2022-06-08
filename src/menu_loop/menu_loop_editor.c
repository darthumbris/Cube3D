/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_loop_editor.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:54:45 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/08 15:55:15 by shoogenb      ########   odam.nl         */
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

void	move_map(t_data *data, t_menu *menu)
{
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_LEFT) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_A))
		menu->map_offset.x -= MAP_TRANSLATE_SPEED;
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_RIGHT) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_D))
		menu->map_offset.x += MAP_TRANSLATE_SPEED;
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_DOWN) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_S))
		menu->map_offset.y += MAP_TRANSLATE_SPEED;
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_UP) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_W))
		menu->map_offset.y -= MAP_TRANSLATE_SPEED;
	if (is_movement_key_down(data->mlx.mlx_handle))
		data->menu.update = true;
	if (menu->map_offset.x < -.4)
		menu->map_offset.x = -.4;
	if (menu->map_offset.x > MAX_MAP_SIZE - menu->max_tiles_on_map.x - 0.4)
		menu->map_offset.x = MAX_MAP_SIZE - menu->max_tiles_on_map.x - 0.4;
	if (menu->map_offset.y > MAX_MAP_SIZE - menu->max_tiles_on_map.y - 0.4)
			menu->map_offset.y = MAX_MAP_SIZE - menu->max_tiles_on_map.y - 0.4;
	if (menu->map_offset.y < -.4)
		menu->map_offset.y = -.4;
}

void	check_hover(t_data *data)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(data->mlx.mlx_handle, &x, &y);
	if (is_hover(&data->menu.enemy_btn, x, y) || \
		is_hover(&data->menu.obj_btn, x, y) || \
		is_hover(&data->menu.floor_btn, x, y) || \
		is_hover(&data->menu.plane_ddlst.active, x, y) || \
		is_hover(&data->menu.floor_ddlst.active, x, y) || \
		is_hover(&data->menu.bucket_btn, x, y) || \
		is_hover(&data->menu.pen_btn, x, y) || \
		is_hover(&data->menu.area_btn, x, y) || \
		is_hover(&data->menu.picker_btn, x, y) || \
		is_hover(&data->menu.load_btn, x, y) || \
		is_hover(&data->menu.save_btn, x, y) || \
		(data->menu.plane_ddlst.active.active == true && \
		is_mouse_in_rect(x, y, data->menu.plane_ddlst.open_rct)) || \
		(data->menu.floor_ddlst.active.active == true && \
		is_mouse_in_rect(x, y, data->menu.floor_ddlst.open_rct)))
		data->menu.update = true;
}
