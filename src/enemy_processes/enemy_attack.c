/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_attack.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 13:35:59 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/16 14:05:01 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	get_max_dist(double player_angle, bool running)
{
	int	max_dist;

	if (player_angle < M_PI && running)
		max_dist = 9;
	else if (running)
		max_dist = 19;
	else if (player_angle && !running)
		max_dist = 15;
	else
		max_dist = 31;
	return (max_dist);
}

static bool	check_running(t_data *data)
{
	return (((mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_W) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_S) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_A) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_D)) && \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_LEFT_SHIFT)));
}

static double	get_dodge_chance(t_sprite *sprite, bool running, \
				double player_angle)
{
	double	dodge_chance;

	dodge_chance = 0;
	if (running)
		dodge_chance += 0.375; //dodge chance increases when running.
	if (player_angle < M_PI)
		dodge_chance += .0625 * sqrt(sprite->dist);
	else
		dodge_chance += .03125 * sqrt(sprite->dist);
	if (sprite->dist < 2 && player_angle >= M_PI - M_PI_8 && \
		player_angle <= M_PI + M_PI_8)
		dodge_chance = 0; //point blank shot at players back;
	return (dodge_chance);
}

static void	damage_player(t_data *data, double dodge_chance, t_sprite *sprite, \
							int max_dist)
{
	const double	dist = sqrt(sprite->dist);
	int				damage;
	double			hit;

	if (dist > max_dist)
	{
		if (DEBUG_MODE)
			printf("enemy too far. Misses player\n");
		return ;
	}
	damage = rand() % 256;
	hit = (rand() % 100) / (double)100;
	if (dist <= 1.0 && hit > dodge_chance && (damage / 4) > 63)
		damage = 63;
	else
		damage /= 4;
	if (dist <= 3.0 && hit > dodge_chance && (damage / 2) > 31)
		damage = 31;
	else
		damage /= 2;
	if (((hit > dodge_chance && sprite->kind == GUARD) || \
		(sprite->kind == DOG && hit > 0.30)) && (damage / 2) > 15)
		damage = 15;
	else
		damage /= 2;
	if (DEBUG_MODE)
		printf("player took: %d damage, current health: %d\n", damage, data->player.health);
	data->player.health -= damage;
	data->update_hud = true;
	if (data->player.health < 0)
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
}

void	attack_player(t_sprite *sprite, t_data *data)
{
	double	dodge_chance;
	double	player_angle;
	bool	running;
	int		max_dist;

	if (player_oustide_viewing_cone(data, sprite))
		return ;
	player_angle = get_angle_of_attack
		(sprite->map_pos, data->cam.pos, data->cam.dir);
	running = check_running(data);
	max_dist = get_max_dist(player_angle, running);
	dodge_chance = get_dodge_chance(sprite, running, player_angle);
	sprite->en_dat.state = ATTACKING;
	sprite->en_dat.frame = 0;
	sprite->en_dat.played_sound = false;
	damage_player(data, dodge_chance, sprite, max_dist);
}
