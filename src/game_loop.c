/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:33:29 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/10 17:17:36 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	arr_cleanup(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	key_handler(struct mlx_key_data keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keys.key == MLX_KEY_ESCAPE && keys.action != MLX_RELEASE)
	{
		if (data->bonus)
			clear_sprite_lst(&data->sprite_lst);
		arr_cleanup(data->level.unparsed);
		arr_cleanup(data->level.map);
		mlx_close_window(data->mlx.mlx_handle);
		//TODO: cleanup callocs
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
	if (keys.key == MLX_KEY_LEFT_CONTROL && keys.action != MLX_RELEASE)
	{
		data->mlx.weapon_anim[data->player.active_weapon].animate = true;
		if (data->player.ammo > 0 && data->player.active_weapon != KNIFE)
		{
			data->player.ammo--;
			data->update_hud = true;
		}
		check_weapon_hit(data);
	}
	if (keys.key == MLX_KEY_1 && keys.action != MLX_RELEASE)
	{
		data->player.active_weapon = KNIFE;
		draw_weapons(data, data->mlx.weapon_anim[KNIFE].tex0);
	}
	if (keys.key == MLX_KEY_2 && keys.action != MLX_RELEASE && \
		data->player.ammo)
	{
		data->player.active_weapon = PISTOL;
		draw_weapons(data, data->mlx.weapon_anim[PISTOL].tex0);
	}
	if (keys.key == MLX_KEY_3 && keys.action != MLX_RELEASE && \
		data->player.ammo && data->player.machine_gun_pickup)
	{
		data->player.active_weapon = MACHINEGUN;
		draw_weapons(data, data->mlx.weapon_anim[MACHINEGUN].tex0);
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
		if (data->mlx.weapon_anim[data->player.active_weapon].animate)
			animate_weapon(data);
	}
	update_objects(data);
}
