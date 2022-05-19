/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_attack_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 15:36:55 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 10:48:00 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	reset_player(t_data *data)
{
	data->player.health = 100;
	data->player.lives--;
	data->cam.pos.x = data->player.start_pos.x;
	data->cam.pos.y = data->player.start_pos.y;
	data->cam.dir.x = data->player.start_dir.x;
	data->cam.dir.y = data->player.start_dir.y;
	data->cam.plane.x = data->player.start_plane.x;
	data->cam.plane.y = data->player.start_plane.y;
	if (data->player.lives < 0)
	{
		printf("game should stop\n");
		data->player.lives = 0;
		data->player.health = 0;
	}
}

static int	get_damage_to_player(double dist, double hit, \
								double dodge_chance, int kind)
{
	int	damage;

	damage = rand() % 256;
	if (dist <= 1.0 && hit > dodge_chance && (damage / 4) > 63)
		damage = 63;
	else
		damage /= 4;
	if (dist <= 3.0 && hit > dodge_chance && (damage / 2) > 31)
		damage = 31;
	else
		damage /= 2;
	if (((hit > dodge_chance && kind == GUARD) || \
		(kind == DOG && hit > 0.30)) && (damage / 2) > 15)
		damage = 15;
	else
		damage /= 2;
	if (DEBUG_MODE)
		printf("player took: %d damage\n", damage);
	return (damage);
}

void	damage_player(t_data *data, double dodge_chance, t_sprite *enemy, \
							int max_dist)
{
	const double	dist = sqrt(enemy->dist);
	int				damage;
	double			hit;

	if (dist > max_dist)
		return ;
	damage = rand() % 256;
	hit = (rand() % 100) / (double)100;
	damage = get_damage_to_player(dist, hit, dodge_chance, enemy->kind);
	data->player.health -= damage;
	data->update_hud = true;
	if (data->player.health <= 0)
		reset_player(data);
}
