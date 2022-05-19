/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_weapon_hit.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 12:07:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 14:38:16 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	calculate_damage(t_data *data, double dist)
{
	int	damage;

	damage = rand() % 256;
	if (data->player.active_weapon == KNIFE)
	{
		damage = damage / 16;
		if (damage > 15)
			damage = 15;
	}
	else if (dist < 1.5)
	{
		damage = damage / 4;
		if (damage > 63)
			damage = 63;
	}
	else
		damage = damage / 6;
	if ((dist < 4 || (dist < 20 && damage / 12 >= dist)) && damage > 42)
			damage = 42;
	else if (dist < 21 && damage / 12 >= dist && damage > 39)
		damage = 39;
	else if (dist > 21)
		damage = 0;
	return (damage);
}

static void	play_death_sound(t_data *data, t_sprite *enemy)
{
	if (enemy->kind == GUARD)
		play_sound_vol(data, "./assets/wav_files/sounds/grddth1.wav", \
			enemy->dist);
	else
		play_sound_vol(data, "./assets/wav_files/sounds/dogdth.wav", \
			enemy->dist);
}

static void	damage_enemy(t_data *data, t_sprite *enemy, int damage)
{
	enemy->en_dat.health -= damage;
	if (DEBUG_MODE)
		printf("damage: %d, enemy health: %d\n", \
			damage, enemy->en_dat.health);
	if (enemy->en_dat.health > 0)
	{
		enemy->en_dat.state = HURT;
		alert_neighbouring_enemies(data, enemy);
	}
	else
	{
		data->player.enemies_killed++;
		play_death_sound(data, enemy);
		enemy->en_dat.state = DYING;
		enemy->en_dat.frame = 0;
		data->player.score += 100;
		if (enemy->kind == GUARD)
			add_ammo_to_lst(&data->sprite_lst, *enemy);
		else
			data->player.score += 100;
	}
}

void	check_weapon_hit(t_data *data)
{
	t_sprite_lst	*enemy;

	enemy = get_enemie_hit(data);
	sound_alerts_enemies(data);
	if (!enemy)
	{
		if (DEBUG_MODE)
			printf("miss\n");
		return ;
	}
	draw_enemies(data, &enemy->sprite_data);
	damage_enemy(data, &enemy->sprite_data, \
		calculate_damage(data, round(sqrt(enemy->sprite_data.dist))));
}
