/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:33:29 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/13 09:37:00 by shoogenb      ########   odam.nl         */
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

	lst = data->sprite_lst;
	delay++;
	while (lst)
	{
		if ((lst->sprite_data.kind == GUARD || lst->sprite_data.kind == DOG) \
			&& lst->sprite_data.state == ATTACKING)
		{
			if (delay % 16 == 0)
				lst->sprite_data.frame++;
			if (lst->sprite_data.state == ATTACKING && lst->sprite_data.frame > 2)
			{
				lst->sprite_data.frame = 0;
				lst->sprite_data.state = ALIVE;
			}
		}
		else if ((lst->sprite_data.kind == GUARD || lst->sprite_data.kind == DOG) \
			&& lst->sprite_data.state == ALIVE && lst->sprite_data.last_attack)
		{
			lst->sprite_data.last_attack++;
			if (lst->sprite_data.last_attack > 30)
				lst->sprite_data.last_attack = 0;
		}
		lst = lst->next;
	}
	if (delay > 48)
		delay = 0;
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
			&& lst->sprite_data.state == DYING)
		{
			if (delay % 8 == 0)
				lst->sprite_data.frame++;
			if (lst->sprite_data.state == ATTACKING && lst->sprite_data.frame > 2)
				lst->sprite_data.frame = 2;
			if (lst->sprite_data.kind == GUARD && lst->sprite_data.frame > 4)
			{
				lst->sprite_data.state = DEAD;
				lst->sprite_data.frame = 4;
			}
			else if (lst->sprite_data.kind == DOG && lst->sprite_data.frame > 3)
			{
				lst->sprite_data.state = DEAD;
				lst->sprite_data.frame = 3;
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
