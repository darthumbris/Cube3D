/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:33:29 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/09 13:35:59 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	key_handler(struct mlx_key_data keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keys.key == MLX_KEY_ESCAPE && keys.action != MLX_RELEASE)
	{
		if (data->bonus)
			clear_sprite_lst(&data->sprite_lst);
		mlx_close_window(data->mlx.mlx_handle);
		//TODO free everything properly.
	}
	if (keys.key == MLX_KEY_KP_SUBTRACT && keys.action != MLX_RELEASE)
	{
		data->mlx.minimap_zoom += 1;
		if (data->mlx.minimap_zoom > 20)
			data->mlx.minimap_zoom = 20;
	}	
	if (keys.key == MLX_KEY_KP_ADD && keys.action != MLX_RELEASE)
	{
		data->mlx.minimap_zoom -= 1;
		if (data->mlx.minimap_zoom < 2)
			data->mlx.minimap_zoom = 2;
	}
}

static void	movement_handler(t_data *data)
{
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_LEFT))
		change_camera_angle(data, -1);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_RIGHT))
		change_camera_angle(data, +1);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_W))
		move_camera_pos(data, +1, false);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_S))
		move_camera_pos(data, -1, false);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_A))
		move_camera_pos(data, -1, true);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_D))
		move_camera_pos(data, +1, true);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_E))
		is_nearby_door(data);
}

static void	mouse_handler(t_data *data)
{
	static int	oldx = 0;
	int			x;
	int			y;

	mlx_get_mouse_pos(data->mlx.mlx_handle, &x, &y);
	if (oldx == 0)
		oldx = x;
	if (x > oldx)
		change_camera_angle(data, +1);
	else if (x < oldx)
		change_camera_angle(data, -1);
	oldx = x;
}

void	game_loop(void *v_data)
{
	t_data		*data;

	data = (t_data *)v_data;
	movement_handler(data);
	mouse_handler(data);
	raycaster(data);
	if (data->bonus)
	{
		draw_sprites(data);
		if (data->update_hud)
		{
			draw_hud(data);
			draw_numbers(data);
			data->update_hud = false;
		}
		if (data->delay > 50)
		{
			draw_faces(data);
			data->delay = 0;
		}
		draw_minimap(data);
		data->delay++;
	}
	update_objects(data);
}
