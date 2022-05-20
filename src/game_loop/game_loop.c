/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:33:29 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/20 11:16:23 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
}

static void	update_objects(t_data *data)
{
	update_doors(data, -1);
	update_secret_walls(data);
	update_items(data);
}

static void	bonus_loop(t_data *data)
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
	if (data->delay % 3 == 0)
		draw_minimap(data);
	data->delay++;
	if (data->mlx.weapon_anim[data->player.active_weapon].animate)
		animate_weapon(data);
	update_objects(data);
}

void	game_loop(void *v_data)
{
	t_data		*data;
	static int	delay = 100;

	data = (t_data *)v_data;
	if (!data->player.game_over)
	{
		movement_handler(data);
		mouse_handler(data);
		raycaster(data);
	}
	if (data->bonus)
	{
		if (!data->player.game_over)
			bonus_loop(data);
		else if (delay > 0)
			delay--;
		else
			mlx_image_to_window(data->mlx.mlx_handle, data->mlx.score_screen, 0, 0);
		soundtrack(data);
	}
}
