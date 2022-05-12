/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_weapon_hit.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 12:07:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/12 16:24:14 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static double	get_enemey_dist(t_line *l, t_vector_double pos)
{
	return (fabs(l->a * pos.x + l->b * pos.y + l->c) / \
			sqrt(l->a * l->a + l->b * l->b));
}

static bool	is_in_front(t_vector_double en_pos, t_camera cam, double dist)
{
	bool			x_dir;
	bool			y_dir;

	x_dir = false;
	y_dir = false;
	if (cam.dir.x >= 0 && en_pos.x >= cam.pos.x)
		x_dir = true;
	else if (cam.dir.x < 0 && en_pos.x < cam.pos.x)
		x_dir = true;
	if (cam.dir.y >= 0 && en_pos.y >= cam.pos.y)
		y_dir = true;
	else if (cam.dir.y < 0 && en_pos.y < cam.pos.y)
		y_dir = true;
	if (dist < 1.2 && (x_dir || y_dir))
		return (true);
	return (x_dir && y_dir);
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
			&& (last->sprite_data.state == ALIVE || \
			last->sprite_data.state == ATTACKING))
		{
			fov = get_enemey_dist(&data->caster.dcas.l1, \
				last->sprite_data.map_pos);
			if (fov <= WEAPON_FOV && (last->sprite_data.state == ALIVE || \
			last->sprite_data.state == ATTACKING) && \
			is_in_front(last->sprite_data.map_pos, data->cam, \
				last->sprite_data.dist))
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
	{
		if (DEBUG_MODE)
			printf("miss\n");
		return ;
	}
	draw_enemies(data, &enemy->sprite_data);
	damage = calculate_damage(data, round(sqrt(enemy->sprite_data.dist)));
	enemy->sprite_data.health -= damage;
	if (DEBUG_MODE)
		printf("damage: %d, enemy health: %d\n", \
			damage, enemy->sprite_data.health);
	if (enemy->sprite_data.health > 0)
		enemy->sprite_data.player_detected = true;
	else
	{
		enemy->sprite_data.state = DYING;
		enemy->sprite_data.frame = 0;
		if (enemy->sprite_data.kind == GUARD)
			add_ammo_to_lst(&data->sprite_lst, enemy->sprite_data);
		if (enemy->sprite_data.kind == GUARD)
			data->player.score += 100;
		else
			data->player.score += 200;
	}
}
