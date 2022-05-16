/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:33:29 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/16 15:13:43 by shoogenb      ########   odam.nl         */
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
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_E))
		is_nearby_door(data);
}

static void	check_enemies_attack(t_data *data)
{
	t_sprite_lst	*lst;
	static int		delay = 0;
	static int		delay_target = 0;

	lst = data->sprite_lst;
	delay++;
	delay_target++;
	while (lst)
	{
		if ((lst->sprite_data.kind == GUARD || lst->sprite_data.kind == DOG) \
			&& lst->sprite_data.en_dat.state == ATTACKING)
		{
			if (lst->sprite_data.en_dat.frame == 1 && !lst->sprite_data.en_dat.played_sound)
			{
				printf("playing sound\n");
				if (lst->sprite_data.kind == DOG)
    				ma_engine_play_sound(&data->sound.engine, "./assets/wav_files/sounds/dogatk.wav", &data->sound.sfx);
				if (lst->sprite_data.kind == GUARD)
					ma_engine_play_sound(&data->sound.engine, "./assets/wav_files/sounds/grdatk.wav", &data->sound.sfx);
				lst->sprite_data.en_dat.played_sound = true;
			}
			if (delay % 16 == 0)
				lst->sprite_data.en_dat.frame++;
			if (lst->sprite_data.en_dat.frame > 2)
			{
				lst->sprite_data.en_dat.frame = 0;
				lst->sprite_data.en_dat.state = TRACKING;
			}
		}
		else if ((lst->sprite_data.kind == GUARD || lst->sprite_data.kind == DOG) \
			&& lst->sprite_data.en_dat.state == ALIVE && lst->sprite_data.en_dat.last_attack)
		{
			lst->sprite_data.en_dat.last_attack++;
			if (lst->sprite_data.en_dat.last_attack > 50)
				lst->sprite_data.en_dat.last_attack = 0;
		}
		lst = lst->next;
	}
	if (delay > 48)
		delay = 0;
	if (delay_target > 50)
		delay_target = 0;
}

static void	check_enemies_dead(t_data *data)
{
	t_sprite_lst	*lst;
	static int		delay = 0;

	lst = data->sprite_lst;
	delay++;
	while (lst)
	{
		if ((lst->sprite_data.kind == GUARD || lst->sprite_data.kind == DOG) \
			&& lst->sprite_data.en_dat.state == DYING)
		{
			if (delay % 8 == 0)
				lst->sprite_data.en_dat.frame++;
			if (lst->sprite_data.kind == GUARD && lst->sprite_data.en_dat.frame > 4)
			{
				lst->sprite_data.en_dat.state = DEAD;
				lst->sprite_data.en_dat.frame = 4;
			}
			else if (lst->sprite_data.kind == DOG && lst->sprite_data.en_dat.frame > 3)
			{
				lst->sprite_data.en_dat.state = DEAD;
				lst->sprite_data.en_dat.frame = 3;
			}
		}
		lst = lst->next;
	}
	if (delay > 48)
		delay = 0;
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
	draw_minimap(data);
	data->delay++;
	if (data->mlx.weapon_anim[data->player.active_weapon].animate)
		animate_weapon(data);
	update_objects(data);
	check_enemies_dead(data);
	check_enemies_attack(data);
}

void	game_loop(void *v_data)
{
	t_data		*data;

	data = (t_data *)v_data;
	movement_handler(data);
	mouse_handler(data);
	raycaster(data);
	if (data->bonus)
		bonus_loop(data);
}
