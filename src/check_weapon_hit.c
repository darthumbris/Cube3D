/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_weapon_hit.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 12:07:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 14:15:25 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

double	get_angle_of_attack(t_vector_double target_pos, \
	t_vector_double attacker_pos, t_vector_double attacker_dir)
{
	return (fabs(atan2(attacker_dir.y, attacker_dir.x) - \
		atan2(target_pos.y - attacker_pos.y, target_pos.x - attacker_pos.x)));
}

bool	is_target_visible(t_vector_double target_pos, \
	t_vector_double attacker_pos, t_vector_double attacker_dir, t_data *data)
{
	t_vector_double	ray_pos;
	t_vector_double	ray_posfloor;
	char			c;

	ray_pos = attacker_pos;
	while (ray_pos.x < data->level.map_w && ray_pos.x > 0 && \
			ray_pos.y < data->level.map_h && ray_pos.y > 0)
	{
		ray_posfloor.x = (ray_pos.x - ((ray_pos.x - floor(ray_pos.x))));
		ray_posfloor.y = (ray_pos.y - ((ray_pos.y - floor(ray_pos.y))));
		c = data->level.map[(int)ray_posfloor.y][(int)ray_posfloor.x];
		if ((int)ray_pos.x == (int)target_pos.x && \
			(int)ray_pos.y == (int)target_pos.y)
			return (true);
		if (is_wall_tile(c) || door_check(data, \
			(t_vector_int){(int)ray_pos.x, (int)ray_pos.y}))
			return (false);
		ray_pos.x += attacker_dir.x;
		ray_pos.y += attacker_dir.y;
	}
	return (true);
}

t_sprite_lst	*find_enemy(t_data *data, double range)
{
	t_sprite_lst	*last;
	double			fov;

	last = data->sprite_lst;
	while (last && last->next)
		last = last->next;
	while (last)
	{
		if (last->sprite_data.dist >= range)
			return (NULL);
		if ((last->sprite_data.kind == GUARD || last->sprite_data.kind == DOG) \
			&& last->sprite_data.en_dat.state < DYING)
		{
			fov = get_angle_of_attack(last->sprite_data.map_pos, \
				data->cam.pos, data->cam.dir);
			if (is_target_visible(last->sprite_data.map_pos, \
				data->cam.pos, data->cam.dir, data) && (fov <= WEAPON_FOV || \
				(last->sprite_data.dist < 2 && fov < MELEE_FOV)))
				return (last);
		}
		last = last->prev;
	}
	return (NULL);
}

t_sprite_lst	*get_enemie_hit(t_data *data)
{
	if (data->player.active_weapon == KNIFE)
		return (find_enemy(data, KNIFE_RANGE));
	return (find_enemy(data, GUN_RANGE));
}

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

//TODO fix this so it uses spritesheet?
void	check_weapon_hit(t_data *data)
{
	t_sprite_lst	*enemy;
	int				damage;

	enemy = get_enemie_hit(data);
	sound_alerts_enemies(data);
	if (!enemy)
	{
		if (DEBUG_MODE)
			printf("miss\n");
		//TODO make enemies near the sound of this shot get alerted
		return ;
	}
	draw_enemies(data, &enemy->sprite_data);
	damage = calculate_damage(data, round(sqrt(enemy->sprite_data.dist)));
	enemy->sprite_data.en_dat.health -= damage;
	if (DEBUG_MODE)
		printf("damage: %d, enemy health: %d\n", \
			damage, enemy->sprite_data.en_dat.health);
	if (enemy->sprite_data.en_dat.health > 0)
		alert_neighbouring_enemies(data, &enemy->sprite_data);
	else
	{
		enemy->sprite_data.en_dat.state = DYING;
		enemy->sprite_data.en_dat.frame = 0;
		if (enemy->sprite_data.kind == GUARD)
		{
			add_ammo_to_lst(&data->sprite_lst, enemy->sprite_data);
    		ma_engine_play_sound(&data->sound.engine, "./assets/wav_files/sounds/grddth1.wav", &data->sound.sfx);
			data->player.score += 100;
		}
		else
		{
			data->player.score += 200;
    		ma_engine_play_sound(&data->sound.engine, "./assets/wav_files/sounds/dogdth.wav", &data->sound.sfx);	
		}
	}
}
