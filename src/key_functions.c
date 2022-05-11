/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 11:24:54 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/11 11:33:52 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	arr_cleanup(char **arr)
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

static void	cleanup_data(t_data *data)
{
	if (data->bonus)
	{
		clear_sprite_lst(&data->sprite_lst);
		if (data->doors)
			free(data->doors);
		if (data->secrets)
			free(data->secrets);
	}
	arr_cleanup(data->level.unparsed);
	arr_cleanup(data->level.map);
	if (data->config.dat)
		free(data->config.dat); // DO this properly key in the config data needs to be freed
	//TODO: cleanup callocs
}

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

void	key_handler(struct mlx_key_data keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keys.key == MLX_KEY_ESCAPE && keys.action != MLX_RELEASE)
	{
		cleanup_data(data);
		mlx_close_window(data->mlx.mlx_handle);
		exit(EXIT_SUCCESS);
	}
	if (data->bonus)
	{
		minimap_keys(data, keys);
		if (keys.key == MLX_KEY_LEFT_CONTROL && \
			keys.action != MLX_RELEASE)
		{
			data->mlx.weapon_anim[data->player.active_weapon].animate = true;
			if (data->player.ammo > 0 && data->player.active_weapon != KNIFE)
			{
				data->player.ammo--;
				data->update_hud = true;
			}
			check_weapon_hit(data);
		}
		weapon_switch(data, keys);
	}
}
