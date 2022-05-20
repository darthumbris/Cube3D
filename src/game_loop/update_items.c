/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_items.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:37:04 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/20 10:30:52 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	health_item(t_data *data, t_sprite_lst *item, int kind)
{
	if (data->player.health < 100 && (kind == MEDKIT || \
			kind == DOGMEAL || kind == STIMULANT))
		simple_heal_item(data, item, kind);
	if (kind == SOUL)
	{
		data->player.health = 100;
		data->player.lives++;
		if (data->player.lives > 9)
			data->player.lives = 9;
		data->player.ammo += 25;
		data->update_hud = true;
		item->sprite_data.kind = 0;
	}
}

void	ammo_item(t_data *data, t_sprite_lst *item)
{
	if (data->player.ammo < 99)
	{
		if (item->sprite_data.kind == AMMO)
		{
			if (data->player.active_weapon == KNIFE && data->player.ammo == 0)
			{
				if (data->player.machine_gun_pickup)
					data->player.active_weapon = MACHINEGUN;
				else
					data->player.active_weapon = PISTOL;
				draw_weapons(data, data->mlx.weapon_anim
				[data->player.active_weapon].tex0, data->mlx.weapon);
			}
			if (!item->sprite_data.dropped)
				data->player.ammo += 8;
			else
				data->player.ammo += 4;
			ma_engine_play_sound(&data->sound.engine, \
				"./assets/wav_files/sounds/ammoup.wav", &data->sound.sfx_g);
			item->sprite_data.kind = 0;
			data->update_hud = true;
		}
	}
	if (data->player.ammo > 99)
		data->player.ammo = 99;
}

void	treasure_item(t_data *data, t_sprite *treasure)
{
	if (treasure->kind == TREASURE_0)
	{
		ma_engine_play_sound(&data->sound.engine, \
			"./assets/wav_files/sounds/cross.wav", &data->sound.sfx_g);
		data->player.score += 100;
	}
	else if (treasure->kind == TREASURE_1)
	{
		ma_engine_play_sound(&data->sound.engine, \
			"./assets/wav_files/sounds/chalice.wav", &data->sound.sfx_g);
		data->player.score += 500;
	}
	else if (treasure->kind == TREASURE_2)
	{
		ma_engine_play_sound(&data->sound.engine, \
		"./assets/wav_files/sounds/chest.wav", &data->sound.sfx_g);
		data->player.score += 1000;
	}
	if (treasure->kind == TREASURE_0 || treasure->kind == TREASURE_1 || \
		treasure->kind == TREASURE_2)
	{
		data->update_hud = true;
		treasure->kind = 0;
		data->player.treasure_found++;
	}
}

void	weapon_item(t_data *data, t_sprite_lst *item)
{
	if (item->sprite_data.kind == GUN)
	{
		data->player.active_weapon = MACHINEGUN;
		data->player.machine_gun_pickup = true;
		data->player.ammo += 6;
		data->update_hud = true;
		if (data->player.ammo > 99)
			data->player.ammo = 99;
		item->sprite_data.kind = 0;
		draw_weapons(data, data->mlx.weapon_anim[MACHINEGUN].tex0, \
					data->mlx.weapon);
	}
}

//TODO make sure to delete the item from the itemlist after pickup
void	update_items(t_data *data)
{
	t_sprite_lst	*lst;

	lst = data->sprite_lst;
	while (lst)
	{
		if (is_item(lst->sprite_data.kind) && \
		lst->sprite_data.dist < PICKUP_DIST && \
		sprite_dist(lst->sprite_data.map_pos, data->cam.pos) < PICKUP_DIST)
		{
			health_item(data, lst, lst->sprite_data.kind);
			ammo_item(data, lst);
			treasure_item(data, &lst->sprite_data);
			weapon_item(data, lst);
		}
		lst = lst->next;
	}
}
