/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_weapon_hit.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 12:07:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/10 17:04:08 by shoogenb      ########   odam.nl         */
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

void	check_weapon_hit(t_data *data)
{
	t_sprite_lst	*enemy;
	int				damage;
	double			dist;

	enemy = get_enemie_hit(data);
	if (!enemy)
	{
		printf("miss\n");
		return ;
	}
	dist = round(sqrt(enemy->sprite_data.dist));
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
	else if (dist < 4 || (dist < 20 && damage / 12 >= dist))
	{
		damage = damage / 6;
		if (damage > 42)
			damage = 42;
	}
	else if (dist < 21 && damage / 12 >= dist)
		damage = damage / 6;
	enemy->sprite_data.health -= damage;
	if (enemy->sprite_data.health > 0)
		enemy->sprite_data.player_detected = true;
	else
	{
		enemy->sprite_data.alive = false;
		if (enemy->sprite_data.kind == GUARD)
			enemy->sprite_data.kind = DEAD_GUARD;
		else
		{
			enemy->sprite_data.kind = DEAD_DOG;
			enemy->sprite_data.transp_begin.x = 8;
			enemy->sprite_data.transp_end.x = 110;
			enemy->sprite_data.transp_end.y = 101;
		}
		data->player.score += 100;
		//TODO add a sprite for ammo to the list when a guard dies.
	}
	printf("damage: %d\tdist: %f\n", damage, dist);
}
