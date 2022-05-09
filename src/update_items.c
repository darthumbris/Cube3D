/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_items.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:37:04 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/09 14:37:04 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	health_item(t_data *data, t_sprite_lst *item)
{
	if (data->player.health < 100)
	{
		if (item->sprite_data.kind == MEDKIT)
			data->player.health += 25;
		else if (item->sprite_data.kind == DOGMEAL)
			data->player.health += 4;
		else if (item->sprite_data.kind == STIMULANT)
			data->player.health += 10;
		if (data->player.health > 100)
			data->player.health = 100;
		//Need to remove the item from the list.
		data->update_hud = true;
		item->sprite_data.kind = 0;
	}
	if (item->sprite_data.kind == SOUL)
	{
		data->player.health = 100;
		data->player.lives++;
		if (data->player.lives > 9)
			data->player.lives = 9;
		data->player.ammo += 25;
		data->player.score += 10000;
		data->update_hud = true;
		item->sprite_data.kind = 0;
		//Need to remove the item.
	}
}

void	ammo_item(t_data *data, t_sprite_lst *item)
{
	if (data->player.ammo < 99)
	{
		if (item->sprite_data.kind == AMMO)
		{
			data->player.ammo += 8;
			item->sprite_data.kind = 0;
			data->update_hud = true;
		}
		if (data->player.ammo > 99)
			data->player.ammo = 99;
		//Need to remove the item from the list.
	}
	else if (data->player.ammo > 99)
		data->player.ammo = 99;
}

void	treasure_item(t_data *data, t_sprite_lst *item)
{
	if (item->sprite_data.kind == TREASURE_0)
	{
		data->player.score += 100;
		data->update_hud = true;
		item->sprite_data.kind = 0;
	}
	else if (item->sprite_data.kind == TREASURE_1)
	{
		data->player.score += 500;
		data->update_hud = true;
		item->sprite_data.kind = 0;
	}
	else if (item->sprite_data.kind == TREASURE_2)
	{
		data->player.score += 1000;
		data->update_hud = true;
		item->sprite_data.kind = 0;
	}
	//Need to remove the item from the list.
}

void	update_items(t_data *data)
{
	t_sprite_lst	*lst;
	int				counter;

	lst = data->sprite_lst;
	counter = 0;
	while (lst)
	{
		if (lst->sprite_data.dist < PICKUP_DIST && \
		sprite_dist(lst->sprite_data.map_pos, data->cam.pos) < PICKUP_DIST)
		{
			health_item(data, lst);
			ammo_item(data, lst);
			treasure_item(data, lst);
		}
		counter++;
		lst = lst->next;
	}
}
