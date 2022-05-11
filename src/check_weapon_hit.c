/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_weapon_hit.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 12:07:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/11 17:02:24 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static double	get_enemey_dist(t_line *l, t_vector_double pos)
{
	return (fabs(l->a * pos.x + l->b * pos.y + l->c) / \
			sqrt(l->a * l->a + l->b * l->b));
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
			&& last->sprite_data.health)
		{
			fov = get_enemey_dist(&data->caster.dcas.l1, \
				last->sprite_data.map_pos);
			if (fov <= WEAPON_FOV)
				return (last);
		}
		last = last->prev;
	}
	return (NULL);
}

t_sprite_lst	*get_enemie_hit(t_data *data)
{
	double	weapon_range;

	data->caster.dcas.ray.p_0.x = data->cam.pos.x;
	data->caster.dcas.ray.p_0.y = data->cam.pos.y;
	data->caster.dcas.ray.p_1.x = data->cam.pos.x + data->cam.dir.x;
	data->caster.dcas.ray.p_1.y = data->cam.pos.y + data->cam.dir.y;
	segment_to_line(&data->caster.dcas.ray, &data->caster.dcas.l1);
	if (data->player.active_weapon == KNIFE)
		weapon_range = KNIFE_RANGE;
	else
		weapon_range = GUN_RANGE;
	return (find_enemy(data, weapon_range));
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
	if (!enemy)
		return ;
	draw_enemies(data, &enemy->sprite_data);
	damage = calculate_damage(data, round(sqrt(enemy->sprite_data.dist)));
	enemy->sprite_data.health -= damage;
	if (enemy->sprite_data.health > 0)
		enemy->sprite_data.player_detected = true;
	else
	{
		enemy->sprite_data.alive = false;
		if (enemy->sprite_data.kind == GUARD)
			add_ammo_to_lst(&data->sprite_lst, enemy->sprite_data);
		data->player.score += 100;
	}
}
