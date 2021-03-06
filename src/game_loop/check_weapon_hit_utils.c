/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_weapon_hit_utils.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 15:09:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 12:02:58 by shoogenb      ########   odam.nl         */
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
		if ((is_wall_tile(c) || door_check(data, ray_posfloor)) \
			&& sprite_dist(target_pos, attacker_pos) > \
			sprite_dist(ray_posfloor, target_pos))
			return (false);
		ray_pos.x += attacker_dir.x;
		ray_pos.y += attacker_dir.y;
	}
	return (true);
}

static t_sprite_lst	*find_enemy(t_data *data, double range)
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
		if ((is_enemy_kind(last->sprite_data.kind)) \
			&& last->sprite_data.en_dat.state < DYING)
		{
			fov = get_angle_of_attack(last->sprite_data.map_pos, \
				data->cam.pos, data->cam.dir);
			if (is_target_visible(last->sprite_data.map_pos, \
				data->cam.pos, data->cam.dir, data) && (fov <= WEAPON_FOV || \
				(last->sprite_data.dist < 5 && fov < MELEE_FOV)))
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
