/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_attack.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 13:35:59 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/22 12:09:40 by shoogenb      ########   odam.nl         */
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
		dodge_chance += 0.375;
	if (player_angle < M_PI)
		dodge_chance += .0625 * sqrt(sprite->dist);
	else
		dodge_chance += .03125 * sqrt(sprite->dist);
	if (sprite->dist < 2 && player_angle >= M_PI - M_PI_8 && \
		player_angle <= M_PI + M_PI_8)
		dodge_chance = 0;
	return (dodge_chance);
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
	sprite->en_dat.state = ATTACK;
	sprite->en_dat.frame = 0;
	sprite->en_dat.played_sound = false;
	damage_player(data, dodge_chance, sprite, max_dist);
}
