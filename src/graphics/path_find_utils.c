/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 15:48:51 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/13 10:41:47 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	door_check(t_data *data, t_vector_int g_pos)
{
	return (is_door_tile(data->level.map[g_pos.y][g_pos.x]) && \
			!is_door_open(data, g_pos.y, g_pos.x));
}

void	set_val(t_vector_int *delta, t_vector_int *sign, \
				t_vector_int pc_pos, t_vector_int g_pos)
{
	delta->x = abs(pc_pos.x - g_pos.x);
	delta->y = abs(pc_pos.y - g_pos.y);
	if (pc_pos.x > g_pos.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (pc_pos.y > g_pos.y)
		sign->y = 1;
	else
		sign->y = -1;
}

bool	view_not_blocked(t_data *data, t_vector_int pc_pos, t_vector_int g_pos)
{
	t_vector_int	sign;
	t_vector_int	delta;
	int				err;

	set_val(&delta, &sign, pc_pos, g_pos);
	err = 2 * (delta.y - delta.x);
	while (1)
	{
		if (is_wall_tile(data->level.map[g_pos.y][g_pos.x]) || \
			door_check(data, g_pos))
			return (false);
		if (g_pos.x == pc_pos.x && g_pos.y == pc_pos.y)
			return (true);
		if (err >= 0)
		{
			g_pos.y += sign.y;
			err = err - 2 * delta.x;
		}
		if (err < 0)
		{
			g_pos.x += sign.x;
			err = err + 2 * delta.y;
		}
	}	
}

void	attack_player(t_sprite *sprite, t_data *data)
{
	double	dodge_chance;
	double	player_angle;
	double	enemy_angle;

	if ((sprite->kind == DOG && sprite->dist >= KNIFE_RANGE) || \
		(sprite->kind == GUARD && sprite->dist >= GUN_RANGE))
		return ;
	dodge_chance = 0;
	player_angle = get_angle_of_attack
		(sprite->map_pos, data->cam.pos, data->cam.dir);
	enemy_angle = get_angle_of_attack
		(data->cam.pos, sprite->map_pos, sprite->dir);
	//printf("angle of player to enemie shooting at player: %f\n", 
		// player_angle);
	if ((mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_W) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_S) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_A) || \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_D)) && \
		mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_LEFT_SHIFT))
		dodge_chance += 0.375; //dodge chance increases when running.
	if (player_angle < M_PI)
		dodge_chance += .0625 * sqrt(sprite->dist);
	else
		dodge_chance += .03125 * sqrt(sprite->dist);
	//printf("dist to player: %f\n", sqrt(sprite->dist));
	if (sprite->dist < 2 && player_angle >= M_PI - M_PI_8 && \
		player_angle <= M_PI + M_PI_8)
		dodge_chance = 0; //point blank shot at players back;
	//printf("dodge chance: %f\n", dodge_chance);
}
