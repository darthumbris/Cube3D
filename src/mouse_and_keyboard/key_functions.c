/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 11:24:54 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/20 13:36:26 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	minimap_keys(t_data *data, struct mlx_key_data keys)
{
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

static void	weapon_switch(t_data *data, struct mlx_key_data keys)
{
	if (keys.key == MLX_KEY_1 && keys.action != MLX_RELEASE)
	{
		data->player.active_weapon = KNIFE;
		draw_weapons(data, data->mlx.weapon_anim[KNIFE].tex0, \
					data->mlx.weapon);
	}
	if (keys.key == MLX_KEY_2 && keys.action != MLX_RELEASE && \
		data->player.ammo)
	{
		data->player.active_weapon = PISTOL;
		draw_weapons(data, data->mlx.weapon_anim[PISTOL].tex0, \
					data->mlx.weapon);
	}
	if (keys.key == MLX_KEY_3 && keys.action != MLX_RELEASE && \
		data->player.ammo && data->player.machine_gun_pickup)
	{
		data->player.active_weapon = MACHINEGUN;
		draw_weapons(data, data->mlx.weapon_anim[MACHINEGUN].tex0, \
					data->mlx.weapon);
	}
}

static void	weapon_action(t_data *data)
{
	data->mlx.weapon_anim[data->player.active_weapon].animate = true;
	if (data->player.ammo > 0 && data->player.active_weapon != KNIFE)
		gun_actions(data);
	else
		ma_engine_play_sound(&data->sound.engine, \
		"./assets/wav_files/sounds/knife.wav", &data->sound.sfx_g);
	check_weapon_hit(data);
}

static void	door_action(t_data *data)
{
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_E))
	{
		if (!is_nearby_door(data))
			if (is_nearby_elevator(data))
				game_over(data);
	}
}

void	key_handler(struct mlx_key_data keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keys.key == MLX_KEY_ESCAPE && keys.action != MLX_RELEASE)
	{
		// cleanup_data(data);
		// mlx_close_hook(data->mlx.mlx_handle, game_loop, param);
		// mlx_close_window(data->mlx.mlx_handle);
		exit(EXIT_SUCCESS);
	}
	if (data->bonus && !data->player.game_over)
	{
		minimap_keys(data, keys);
		if (keys.key == MLX_KEY_LEFT_CONTROL && keys.action != MLX_RELEASE)
			weapon_action(data);
		weapon_switch(data, keys);
	}
	door_action(data);
}
